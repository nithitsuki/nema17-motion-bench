# WeAct Studio STM32G474CEU6 core board — pinout

This page gives the pin map of the WeAct Studio "Long" core board with the
STM32G474CEU6 (QFN48). The data comes from the V1.0 schematic and the PCB
silkscreen. See [`SOURCES.md`](SOURCES.md) for the source files.

## Board facts

| Item | Value |
|---|---|
| MCU | STM32G474CEU6, Cortex-M4F, QFN48 |
| Flash / RAM | 512 KB / 128 KB |
| Max clock | 170 MHz |
| HSE crystal | 8 MHz (PF0/PF1) |
| LSE crystal | 32.768 kHz (PC14/PC15) |
| USB | USB 2.0 full speed, Type-C, device only (PA11/PA12) |
| Regulator | 3.3 V LDO, about 250 mA |
| Input power | 5 V from USB-C, or 5 V on a 5V pin (regulator input range 3.3 V to 5.5 V) |
| PCB size | 61.42 mm x 18.24 mm |
| Header pitch | 2.54 mm |
| SWD | 4-pin header P5 (PA13/PA14 are not on the long headers) |

## How to read the tables

The board has the USB-C connector on the left edge. Count positions from
left to right as you look at the top side with the USB-C on the left.

The two long rows are 20-pin headers:

- **P2** is the top row.
- **P1** is the bottom row.

The two short headers at the left end are power headers:

- **P4** is top left, 4 pins.
- **P3** is bottom left, 4 pins.

The silkscreen uses short names. `B11` means PB11, `A5` means PA5, `C6`
means PC6. `NR` means NRST. `V+` means VREF+. `VB` means VBAT.

## Top edge (P4, then P2)

| Pos | Label | MCU pin | QFN48 pin | Notes |
|---:|---|---|---:|---|
| 1 | G | GND | — | P4.1 |
| 2 | G | GND | — | P4.2 |
| 3 | 3V3 | +3.3 V | — | P4.3, regulator output |
| 4 | 3V3 | +3.3 V | — | P4.4, regulator output |
| 5 | B11 | PB11 | 24 | ADC1_IN14 |
| 6 | B10 | PB10 | 22 | QUADSPI CLK |
| 7 | V+ | VREF+ | 20 | Analog reference, tied to 3V3 through R7 (0 Ω) |
| 8 | B2 | PB2 | 19 | ADC2_IN12, TIM5_CH1 |
| 9 | B1 | PB1 | 18 | ADC1_IN12 |
| 10 | B0 | PB0 | 17 | ADC1_IN15 |
| 11 | C4 | PC4 | 16 | ADC2_IN5, I2C2, USART1, QUADSPI |
| 12 | A7 | PA7 | 15 | SPI1_MOSI, TIM1_CH1N |
| 13 | A6 | PA6 | 14 | SPI1_MISO |
| 14 | A5 | PA5 | 13 | SPI1_SCK |
| 15 | A4 | PA4 | 12 | SPI1_NSS, DAC |
| 16 | A3 | PA3 | 11 | USART2_RX, QUADSPI_CLK |
| 17 | A2 | PA2 | 10 | USART2_TX |
| 18 | A1 | PA1 | 9 | ADC1_IN2 |
| 19 | A0 | PA0 | 8 | ADC1_IN1 |
| 20 | NR | NRST | 7 | Reset, active low |
| 21 | C13 | PC13 | 2 | User key, active high |
| 22 | VB | VBAT | 1 | Backup supply, diode-linked to 3V3 |
| 23 | 3V3 | +3.3 V | — | P2.2 |
| 24 | G | GND | — | P2.1 |

## Bottom edge (P3, then P1)

| Pos | Label | MCU pin | QFN48 pin | Notes |
|---:|---|---|---:|---|
| 1 | G | GND | — | P3.1 |
| 2 | G | GND | — | P3.2 |
| 3 | 5V | +5 V | — | P3.3, VDD5V rail |
| 4 | 5V | +5 V | — | P3.4, VDD5V rail |
| 5 | B12 | PB12 | 25 | ADC1_IN11 |
| 6 | B13 | PB13 | 26 | TIM1_CH1N |
| 7 | B14 | PB14 | 27 | TIM1_CH2N, ADC1_IN5 |
| 8 | B15 | PB15 | 28 | TIM1_CH3N |
| 9 | C6 | PC6 | 29 | **User LED, active high**, TIM3_CH1, I2C4 |
| 10 | A8 | PA8 | 30 | I2C2_SDA, TIM1_CH1 |
| 11 | A9 | PA9 | 31 | I2C2_SCL, TIM1_CH2 |
| 12 | A10 | PA10 | 32 | TIM1_CH3 |
| 13 | A11 | PA11 | 33 | **USB DM**, TIM1_CH1N |
| 14 | A12 | PA12 | 34 | **USB DP**, TIM1_CH2N |
| 15 | A15 | PA15 | 38 | SPI1_NSS, I2C1 |
| 16 | C10 | PC10 | 39 | TIM8_CH1N, UART4, SPI3 |
| 17 | C11 | PC11 | 40 | TIM8_CH2N, UART4, SPI3, I2C3 |
| 18 | B3 | PB3 | 41 | SPI1_SCK, USART2 |
| 19 | B4 | PB4 | 42 | SPI1_MISO, USART2 |
| 20 | B5 | PB5 | 43 | SPI1_MOSI |
| 21 | B6 | PB6 | 44 | TIM4_CH1, TIM8_CH1, USART1, FDCAN2 |
| 22 | B7 | PB7 | 45 | I2C1_SDA |
| 23 | B9 | PB9 | 47 | I2C1_SDA, TIM1_CH3N |
| 24 | G | GND | — | P1 end |

## On-board hardware

| Function | Pin | Behaviour |
|---|---|---|
| Blue LED | PC6 | Active high. Set the pin high to light the LED. |
| User key | PC13 | Active high. The key connects PC13 to 3.3 V through 330 Ω. Enable the internal pull-down. |
| Reset key | NRST | Pulls NRST low. |
| BOOT0 key | PB8 | Press and hold to enter the ROM bootloader at the next reset. |
| SWD | PA13 = SWDIO, PA14 = SWCLK | Both go through 330 Ω series resistors to header P5. |
| USB | PA11 = DM, PA12 = DP | Full-speed device only. |

### SWD header P5

| P5 pin | Signal |
|---:|---|
| 1 | GND |
| 2 | SWCLK (PA14) |
| 3 | SWDIO (PA13) |
| 4 | 3.3 V |

## Default Arduino pin map

The STM32duino variant `variant_WEACT_G474CE.h` sets these defaults.

| Peripheral | Pins |
|---|---|
| SPI1 | SCK = PA5, MISO = PA6, MOSI = PA7, SS = PA4 |
| I2C2 | SDA = PA8, SCL = PA9 |
| USART2 | TX = PA2, RX = PA3 |
| USB CDC | PA11 / PA12 |
| `LED_BUILTIN` | PC6 |
| `USER_BTN` | PC13 |

## Pins for motor control

TIM1 has complementary outputs. These pins suit a 3-phase driver or a
current-controlled stepper driver.

| TIM1 output | Pin |
|---|---|
| CH1 | PA8 |
| CH2 | PA9 |
| CH3 | PA10 |
| CH4 | PA11 (alternate function 11 only) |
| CH1N | PB13, PA7, PA11 |
| CH2N | PB14, PB0, PA12 |
| CH3N | PB15, PB1, PB9 |

For a step/direction driver, use any free GPIO. PA0 to PA4 sit next to
each other on the top header (positions 19 to 15).

### TMC2209 suggestion

| TMC2209 signal | Board pin | Header position |
|---|---|---|
| STEP | PA0 | top, 19 |
| DIR | PA1 | top, 18 |
| ENN | PA4 | top, 15 |
| PDN_UART (TX) | PA2 (USART2_TX) | top, 17 |
| PDN_UART (RX) | PA3 (USART2_RX) | top, 16 |
| DIAG | PA5 or PA6 | top, 14 or 13 |

Join TX and RX with a 1 kΩ resistor at the driver side. TMC2209 uses a
single-wire UART on PDN_UART.

For a TMC2130 or another SPI driver, use SPI1 on PA5/PA6/PA7 with a chip
select on PA4 or PA15.

## Power notes

- The 3.3 V LDO supplies about 250 mA. Do not power a motor from it.
- The 5V pins are the VDD5V rail. USB VBUS feeds this rail through D4, a
  Schottky diode. SB1 bypasses D4 when you bridge it.
- Do not connect USB and an external 5 V supply at the same time.
- The 3V3 pins are regulator outputs. Do not feed 3.3 V into them.
- VREF+ connects to 3.3 V through R7, a 0 Ω link. Remove R7 to use an
  external analog reference on the V+ pad.
