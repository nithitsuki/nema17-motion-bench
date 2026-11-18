# Firmware

Firmware test for one NEMA 17 motor driven by a BIGTREETECH TMC2209 V1.3
StepStick. The MCU is a WeAct Studio STM32G474CEU6 "Long" core board.
The project uses PlatformIO with the STM32duino Arduino core.

Pinout: [`../board/STM32G474CEU6-PINOUT.md`](../board/STM32G474CEU6-PINOUT.md)

## What the firmware does

On boot, the firmware holds the driver disabled. It configures the
TMC2209 over the single-wire UART, reads the driver version, and then
enables the driver. It starts the motor at 3200 Hz, which is 1 rev/s at
3200 steps/rev.

Driver settings:

| Register | Value | Meaning |
|---|---|---|
| `GCONF` | `0x000001C1` | VREF pot active, UART control on, 16 microstep select by register, step filter on |
| `IHOLD_IRUN` | `0x00061F10` | IHOLDDELAY 6, IRUN 31, IHOLD 16 |
| `TPOWERDOWN` | `20` | About 0.44 s delay from standstill to current power down |
| `CHOPCONF` | `0x14010053` | TOFF 3, HSTRT 5, HEND 0, TBL 2, 16 microsteps, INTPOL 1 |
| `TPWMTHRS` | `0` | StealthChop at all speeds |

The firmware reads `IOIN` (0x06) and prints the driver version.
A TMC2209 returns `0x21`.

The UART runs at 115200 baud, 8N1, node address 0 (MS1 and MS2 low).
The firmware uses CRC-8 and timeouts, so a missing or unpowered driver
does not stop the console.

The blue LED on PC6 blinks every 500 ms. The console is the native USB
CDC port.

## Console

Open the console with:

```sh
pio device monitor
```

| Key | Action |
|---|---|
| `s` | Start the STEP pulses |
| `x` | Stop the STEP pulses. The driver stays enabled |
| `+` | Multiply the step frequency by 1.25. Maximum 20000 Hz |
| `-` | Divide the step frequency by 1.25. Minimum 100 Hz |
| `d` | Toggle DIR |
| `i` | Print the state and read `DRV_STATUS` (0x6F) |
| `h` | Print the command list |
| `?` | Same as `h` |

The firmware prints the state after each command.

Step frequency and motor speed:

| Step frequency | Speed |
|---:|---:|
| 100 Hz | 0.03 rev/s |
| 3200 Hz | 1.00 rev/s |
| 20000 Hz | 6.25 rev/s |

## Build

```sh
cd firmware
pio run
```

The build writes these files:

- `.pio/build/weact_g474ceu6/firmware.bin` (DFU image, with suffix)
- `.pio/build/weact_g474ceu6/firmware.elf` (ELF image for debugging)

## Flash over USB DFU

The board has the ST ROM DFU bootloader. You need only the USB-C cable.

1. Hold the **BOOT0** key.
2. Tap **NRST** and release it.
3. Release **BOOT0**.
4. Run:

```sh
pio run -t upload
```

The bootloader shows as USB device `0483:df11`. The upload writes to
`0x08000000` and starts the sketch.

If the upload does not start, check the USB cable. Use a cable that
carries data, not only power.

To leave DFU mode, tap **NRST** or unplug the USB cable.

## VREF and current

The VREF pot is set to **1.68 V**. With 0.11 ohm sense resistors, this
sets about **1.19 A RMS** motor current.

Check VREF with a multimeter before you enable the driver:

1. Connect the board and the 24 V motor supply.
2. Put the probe on the VREF test point of the module.
3. Put the ground probe on GND.
4. Turn the pot until the meter shows 1.68 V.

The motor is rated 1.68 A per phase. The firmware uses IRUN 31, so the
VREF voltage sets the current. Do not raise VREF above 1.68 V.

## Safety

- Disconnect the 24 V supply before you change any wire.
- Do not unplug the motor while the driver has power. The driver can
  fail when the motor coil opens under current.
- Keep the driver disabled (EN high) while you connect or disconnect
  the motor.
- The TMC2209 module and the motor become hot. Fit a heatsink on the
  module. Do not touch the module during operation.
- Use a 24 V supply that can supply at least 2 A.
- Connect 3V3 to VIO and connect the grounds together.
- The STEP input must not exceed the driver logic supply.
- Start at a low speed. Increase the speed in small steps.
- Stop the test if the motor stalls, vibrates, or makes a loud noise.

## Implementation notes

- The CRC follows section 4.2 of the TMC2209 datasheet. The datasheet
  processes the bits of each byte LSB first. A GCONF read request at
  node 0 is `05 00 00 48`.
- `PA0` is TIM2 channel 1. The firmware uses `HardwareTimer` with 50
  percent duty.
- This core declares `HardwareSerial` as an abstract interface. The
  concrete serial class is `Uart`, so the firmware uses
  `Uart tmc(PA3, PA2)`.
- The firmware drives PB0 and PB1 low. These pins set MS1 and MS2, which
  select UART node address 0.
- The firmware does not wait for the USB host in `setup()`.
