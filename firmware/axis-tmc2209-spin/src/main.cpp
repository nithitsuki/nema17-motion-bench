// ---------------------------------------------------------------------------
// TMC2209 step/direction spin test for the WeAct Studio STM32G474CEU6 board.
//
// The MCU talks to a BIGTREETECH TMC2209 V1.3 StepStick over a single-wire
// UART, configures the driver, and generates STEP pulses with TIM2 channel 1.
// A USB CDC console on the native USB port controls the motor.
//
// Wiring (fixed):
//   PA0  -> STEP        PA1 -> DIR        PA4 -> EN (active low)
//   PA2  -> USART2_TX   -> 1k -> PDN_UART (module RX)
//   PA3  -> USART2_RX   -> PDN_UART (same node)
//   PB0  -> MS1 (low)   PB1 -> MS2 (low)  => UART node address 0
//   PB10 -> DIAG        PB11 -> INDEX     (not used here)
//   PC6  -> on-board LED (active high)
//
// VREF must be 1.68 V for about 1.19 A RMS with 0.11 ohm sense resistors.
// ---------------------------------------------------------------------------

#include <Arduino.h>

namespace {

// ------------------------------------------------------------------- pins --
constexpr pin_size_t PIN_STEP = PA0;      // TIM2_CH1
constexpr pin_size_t PIN_DIR = PA1;
constexpr pin_size_t PIN_EN = PA4;        // active low
constexpr pin_size_t PIN_TMC_RX = PA3;    // USART2_RX
constexpr pin_size_t PIN_TMC_TX = PA2;    // USART2_TX
constexpr pin_size_t PIN_MS1 = PB0;       // drive low for address 0
constexpr pin_size_t PIN_MS2 = PB1;       // drive low for address 0
constexpr pin_size_t PIN_LED = PC6;       // active high

// ----------------------------------------------------------------- motion --
constexpr uint32_t STEPS_PER_REV = 3200;  // 200 full steps x 16 microsteps
constexpr uint32_t FREQ_START_HZ = 3200;  // 1 rev/s
constexpr uint32_t FREQ_MIN_HZ = 100;
constexpr uint32_t FREQ_MAX_HZ = 20000;
constexpr uint32_t LED_BLINK_MS = 500;

// ------------------------------------------------------------- TMC2209 UART --
constexpr uint8_t TMC_SYNC = 0x05;
constexpr uint8_t TMC_ADDR = 0x00;        // MS1 = MS2 = 0
constexpr uint8_t TMC_REPLY_ADDR = 0xFF;  // master address in a read reply
constexpr uint8_t TMC_WRITE_BIT = 0x80;
constexpr uint32_t TMC_ECHO_TIMEOUT_MS = 5;
constexpr uint32_t TMC_REPLY_TIMEOUT_MS = 20;

constexpr uint8_t REG_GCONF = 0x00;
constexpr uint8_t REG_IOIN = 0x06;
constexpr uint8_t REG_IHOLD_IRUN = 0x10;
constexpr uint8_t REG_TPOWERDOWN = 0x11;
constexpr uint8_t REG_TPWMTHRS = 0x13;
constexpr uint8_t REG_CHOPCONF = 0x6C;
constexpr uint8_t REG_DRV_STATUS = 0x6F;

// I_scale_analog = 1 (keep the VREF pot), pdn_disable = 1,
// mstep_reg_select = 1, multistep_filt = 1.
constexpr uint32_t GCONF_VALUE = 0x000001C1;
// IHOLDDELAY = 6, IRUN = 31, IHOLD = 16.
constexpr uint32_t IHOLD_IRUN_VALUE = (6UL << 16) | (31UL << 8) | 16UL;
constexpr uint32_t TPOWERDOWN_VALUE = 20;
// TOFF = 3, HSTRT = 5, HEND = 0, TBL = 2, VSENSE = 0,
// MRES = 4 (16 microsteps), INTPOL = 1.
constexpr uint32_t CHOPCONF_VALUE = 0x14010053;
constexpr uint32_t TPWMTHRS_VALUE = 0;    // StealthChop at all speeds

constexpr uint8_t TMC2209_VERSION = 0x21;

// ---------------------------------------------------------------- objects --
HardwareTimer step_timer(TIM2);
Uart tmc(PIN_TMC_RX, PIN_TMC_TX);  // rx, tx

uint32_t step_freq_hz = FREQ_START_HZ;
bool motor_running = false;
bool dir_high = false;

// ------------------------------------------------------------- TMC2209 CRC --
// CRC-8, polynomial 0x07, initial value 0, over every byte except the CRC.
// The TMC2209 datasheet (rev 1.09, section 4.2) and the official TMC-API
// process the bits of each byte LSB first. This is not the common MSB-first
// CRC-8 variant. Test vector: a GCONF read request at node 0 is
// 05 00 00 48.
uint8_t tmcCrc(const uint8_t *data, size_t length)
{
  uint8_t crc = 0;
  for (size_t i = 0; i < length; i++) {
    uint8_t current = data[i];
    for (uint8_t bit = 0; bit < 8; bit++) {
      if ((crc >> 7) ^ (current & 0x01)) {
        crc = static_cast<uint8_t>((crc << 1) ^ 0x07);
      } else {
        crc = static_cast<uint8_t>(crc << 1);
      }
      current = static_cast<uint8_t>(current >> 1);
    }
  }
  return crc;
}

// ------------------------------------------------------------- serial input --
// Read exactly length bytes, bounded by an absolute deadline. Returns false
// on timeout instead of blocking forever.
bool readBytes(Uart &port, uint8_t *buffer, size_t length, uint32_t timeout_ms)
{
  const uint32_t start_ms = millis();
  size_t received = 0;

  while (received < length) {
    if (port.available() > 0) {
      buffer[received++] = static_cast<uint8_t>(port.read());
    } else if ((millis() - start_ms) >= timeout_ms) {
      return false;
    }
  }
  return true;
}

void drainInput()
{
  while (tmc.available() > 0) {
    (void)tmc.read();
  }
}

// ---------------------------------------------------------------- TMC2209 IO --
// Write datagram: sync, address, register | 0x80, data 31:0, CRC (8 bytes).
// The transmit line is echoed back on RX, so discard 8 echoed bytes.
bool tmcWrite(uint8_t reg, uint32_t value)
{
  uint8_t frame[8];
  frame[0] = TMC_SYNC;
  frame[1] = TMC_ADDR;
  frame[2] = static_cast<uint8_t>(reg | TMC_WRITE_BIT);
  frame[3] = static_cast<uint8_t>(value >> 24);
  frame[4] = static_cast<uint8_t>(value >> 16);
  frame[5] = static_cast<uint8_t>(value >> 8);
  frame[6] = static_cast<uint8_t>(value);
  frame[7] = tmcCrc(frame, 7);

  drainInput();
  tmc.write(frame, sizeof(frame));
  tmc.flush();

  uint8_t echo[8];
  return readBytes(tmc, echo, sizeof(echo), TMC_ECHO_TIMEOUT_MS);
}

// Read request: sync, address, register, CRC (4 bytes). The reply is
// sync, 0xFF, register, data 31:0, CRC (8 bytes).
bool tmcRead(uint8_t reg, uint32_t &value)
{
  uint8_t request[4];
  request[0] = TMC_SYNC;
  request[1] = TMC_ADDR;
  request[2] = reg;
  request[3] = tmcCrc(request, 3);

  drainInput();
  tmc.write(request, sizeof(request));
  tmc.flush();

  uint8_t echo[4];
  if (!readBytes(tmc, echo, sizeof(echo), TMC_ECHO_TIMEOUT_MS)) {
    return false;
  }

  uint8_t reply[8];
  if (!readBytes(tmc, reply, sizeof(reply), TMC_REPLY_TIMEOUT_MS)) {
    return false;
  }

  if (reply[0] != TMC_SYNC || reply[1] != TMC_REPLY_ADDR || reply[2] != reg) {
    return false;
  }
  if (tmcCrc(reply, 7) != reply[7]) {
    return false;
  }

  value = (static_cast<uint32_t>(reply[3]) << 24) |
          (static_cast<uint32_t>(reply[4]) << 16) |
          (static_cast<uint32_t>(reply[5]) << 8) |
          static_cast<uint32_t>(reply[6]);
  return true;
}

// ------------------------------------------------------------------ output --
void printHex32(uint32_t value)
{
  Serial.print("0x");
  for (int8_t shift = 28; shift >= 0; shift -= 4) {
    const uint8_t nibble = static_cast<uint8_t>((value >> shift) & 0x0F);
    Serial.print(static_cast<char>(nibble < 10 ? ('0' + nibble)
                                               : ('A' + nibble - 10)));
  }
}

void printState()
{
  // Show rev/s without floating point printf support.
  const uint32_t rev_per_s_x100 = (step_freq_hz * 100UL) / STEPS_PER_REV;
  const uint32_t rev_frac = rev_per_s_x100 % 100UL;

  Serial.print("freq=");
  Serial.print(step_freq_hz);
  Serial.print(" Hz  rev/s=");
  Serial.print(rev_per_s_x100 / 100UL);
  Serial.print('.');
  if (rev_frac < 10) {
    Serial.print('0');
  }
  Serial.print(rev_frac);
  Serial.print("  dir=");
  Serial.print(dir_high ? 1 : 0);
  Serial.print("  steps/rev=");
  Serial.print(STEPS_PER_REV);
  Serial.print("  motor=");
  Serial.println(motor_running ? "running" : "stopped");
}

void printHelp()
{
  Serial.println("Commands:");
  Serial.println("  s  start (resume STEP pulses)");
  Serial.println("  x  stop (pause STEP pulses, driver stays enabled)");
  Serial.println("  +  step frequency x 1.25 (max 20000 Hz)");
  Serial.println("  -  step frequency / 1.25 (min 100 Hz)");
  Serial.println("  d  toggle DIR");
  Serial.println("  i  show state and read DRV_STATUS (0x6F)");
  Serial.println("  h  show this list");
  Serial.println("  ?  same as h");
}

void printBanner()
{
  Serial.println();
  Serial.println("TMC2209 NEMA-17 spin test");
  Serial.println("Board: WeAct STM32G474CEU6, TIM2_CH1 STEP on PA0");
  Serial.println("STEP=PA0  DIR=PA1  EN=PA4 (active low)");
  Serial.println("UART: PA2 TX -> 1k -> PDN_UART, PA3 RX on the same node");
  Serial.println("MS1=PB0 low, MS2=PB1 low, UART address 0");
  Serial.println("3200 steps/rev (16 microsteps), 200 full steps/rev");
  Serial.println("VREF must be 1.68 V for about 1.19 A RMS (0.11 ohm sense)");
  Serial.println("Type h or ? for the command list.");
}

// ----------------------------------------------------------------- control --
// Reapply the PWM frequency. setPWM() restarts the timer, so pause it again
// when the motor is meant to stay stopped.
void applyStepFrequency()
{
  step_timer.setPWM(1, PIN_STEP, step_freq_hz, 50);
  if (!motor_running) {
    step_timer.pause();
  }
}

void startMotor()
{
  if (!motor_running) {
    step_timer.resume();
    motor_running = true;
  }
}

void stopMotor()
{
  if (motor_running) {
    step_timer.pause();
    motor_running = false;
  }
}

void configureDriver()
{
  bool uart_ok = true;

  if (!tmcWrite(REG_GCONF, GCONF_VALUE)) {
    uart_ok = false;
  }
  if (!tmcWrite(REG_IHOLD_IRUN, IHOLD_IRUN_VALUE)) {
    uart_ok = false;
  }
  if (!tmcWrite(REG_TPOWERDOWN, TPOWERDOWN_VALUE)) {
    uart_ok = false;
  }
  if (!tmcWrite(REG_CHOPCONF, CHOPCONF_VALUE)) {
    uart_ok = false;
  }
  if (!tmcWrite(REG_TPWMTHRS, TPWMTHRS_VALUE)) {
    uart_ok = false;
  }

  if (!uart_ok) {
    Serial.println("WARN: UART echo timeout while writing registers.");
    Serial.println("WARN: check PA2/PA3, the 1k resistor, and 3V3 on VIO.");
  }

  uint32_t ioin = 0;
  if (!tmcRead(REG_IOIN, ioin)) {
    Serial.println("WARN: no valid reply to IOIN read.");
    Serial.println("WARN: driver may be absent, unpowered, or on another node.");
    Serial.println("WARN: firmware continues without driver identification.");
    return;
  }

  const uint8_t version = static_cast<uint8_t>((ioin >> 24) & 0xFF);
  Serial.print("TMC2209 IOIN = ");
  printHex32(ioin);
  Serial.print("  version = ");
  printHex32(version);
  Serial.println();

  if (version == TMC2209_VERSION) {
    Serial.println("Driver detected: TMC2209.");
  } else {
    Serial.print("WARN: unexpected driver version, expected 0x21, got ");
    printHex32(version);
    Serial.println();
  }
}

void handleCommand(char command, bool &show_drv_status)
{
  switch (command) {
    case 's':
      startMotor();
      break;

    case 'x':
      stopMotor();
      break;

    case '+': {
      uint32_t next = (step_freq_hz * 5UL) / 4UL;
      if (next > FREQ_MAX_HZ) {
        next = FREQ_MAX_HZ;
      }
      if (next != step_freq_hz) {
        step_freq_hz = next;
        applyStepFrequency();
      }
      break;
    }

    case '-': {
      uint32_t next = (step_freq_hz * 4UL) / 5UL;
      if (next < FREQ_MIN_HZ) {
        next = FREQ_MIN_HZ;
      }
      if (next != step_freq_hz) {
        step_freq_hz = next;
        applyStepFrequency();
      }
      break;
    }

    case 'd':
      dir_high = !dir_high;
      digitalWrite(PIN_DIR, dir_high ? HIGH : LOW);
      break;

    case 'i':
      show_drv_status = true;
      break;

    case 'h':
    case '?':
      printHelp();
      break;

    default:
      Serial.print("Unknown command: ");
      Serial.println(command);
      printHelp();
      break;
  }
}

}  // namespace

// -------------------------------------------------------------------- setup --
void setup()
{
  // Hold the driver disabled before the pin becomes an output. The output
  // data register is set first, so enabling the output driver cannot create
  // a low pulse on EN.
  digitalWrite(PIN_EN, HIGH);
  pinMode(PIN_EN, OUTPUT);
  digitalWrite(PIN_EN, HIGH);

  // LED off (active high).
  digitalWrite(PIN_LED, LOW);
  pinMode(PIN_LED, OUTPUT);

  // MS1 and MS2 low select UART node address 0.
  digitalWrite(PIN_MS1, LOW);
  pinMode(PIN_MS1, OUTPUT);
  digitalWrite(PIN_MS2, LOW);
  pinMode(PIN_MS2, OUTPUT);

  // Native USB CDC. Do not wait for the host.
  Serial.begin(115200);

  // TMC2209 single-wire UART: 115200 baud, 8N1.
  tmc.begin(115200, SERIAL_8N1);

  // Give the driver UART time to wake before the first write.
  delay(10);

  // Direction starts low.
  dir_high = false;
  digitalWrite(PIN_DIR, LOW);
  pinMode(PIN_DIR, OUTPUT);

  // Configure 50 percent duty PWM on PA0/TIM2_CH1, then keep it stopped
  // until the driver is configured and enabled.
  step_timer.pause();
  step_timer.setPWM(1, PIN_STEP, step_freq_hz, 50);
  step_timer.pause();
  motor_running = false;

  printBanner();

  configureDriver();

  // Enable the driver, let it settle, then start at 1 rev/s.
  digitalWrite(PIN_EN, LOW);
  delay(500);

  // The timer already runs at FREQ_START_HZ with 50 percent duty, so a
  // resume gives a clean start without extra edges.
  step_freq_hz = FREQ_START_HZ;
  startMotor();

  Serial.print("Auto-start at ");
  Serial.print(step_freq_hz);
  Serial.println(" Hz (1 rev/s).");
  printState();
}

// --------------------------------------------------------------------- loop --
void loop()
{
  static uint32_t last_blink_ms = 0;
  static bool led_on = false;

  if ((millis() - last_blink_ms) >= LED_BLINK_MS) {
    last_blink_ms = millis();
    led_on = !led_on;
    digitalWrite(PIN_LED, led_on ? HIGH : LOW);
  }

  if (Serial.available() > 0) {
    const char command = static_cast<char>(Serial.read());

    // Ignore CR and LF so a terminal that sends CRLF does not produce
    // unknown-command messages.
    if (command == '\r' || command == '\n') {
      return;
    }

    Serial.print("> ");
    Serial.println(command);

    bool show_drv_status = false;
    handleCommand(command, show_drv_status);

    printState();

    if (show_drv_status) {
      uint32_t status = 0;
      if (tmcRead(REG_DRV_STATUS, status)) {
        Serial.print("DRV_STATUS = ");
        printHex32(status);
        Serial.println();
      } else {
        Serial.println("DRV_STATUS read failed (UART timeout or bad reply).");
      }
    }
  }
}
