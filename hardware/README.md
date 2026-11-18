# NEMA 17 + TMC2209 + WeAct STM32G474CEU6

This project contains a KiCad schematic for one stepper axis. The axis uses a
JK42HS48-1684-03F NEMA 17 motor, a BIGTREETECH TMC2209 V1.3 driver module, and
a WeAct Studio STM32G474CEU6 "Long" board.

## Files

| File | Contents |
|---|---|
| `NEMA17-TMC2209.kicad_sch` | The schematic. Open this file in KiCad 9 or 10. |
| `NEMA17-TMC2209.pdf` | A PDF plot of the schematic. |
| `NEMA17-TMC2209.kicad_pro` | The KiCad project file. |
| `NEMA17_TMC2209.kicad_sym` | The two project symbols: the WeAct header and the driver socket. |
| `sym-lib-table` | The symbol library table for the project. |

## Motor data

Source: `../datasheets/JK42HS48-1684-03F NEMA17 5.5 kg-cm Stepper Motor - D-Type Shaft-Nema-17.pdf`.

| Item | Value |
|---|---|
| Step angle | 1.8° |
| Phase current | 1.68 A |
| Phase voltage | 2.8 V |
| Phase resistance | 1.65 Ω ±10% at 20 °C |
| Phase inductance | 2.8 mH ±20% at 1 kHz |
| Holding torque | 4.4 kg·cm (43 N·cm) |
| Insulation class | B (130 °C) |
| Mass | 0.34 kg |
| Body length | 48 mm ±1 mm |
| Flange | 42.3 mm maximum |
| Mounting holes | 4 × M3 × 0.5, 4 mm deep minimum |
| Mounting spacing | 31 mm ±0.2 mm |
| Shaft | 5 mm, 24 mm long, D-cut |
| Leads | 4, UL1007 AWG26, 300 mm |

Wire colours:

| Wire | Coil |
|---|---|
| Red | A+ |
| Green | A− |
| Yellow | B+ |
| Blue | B− |

The vendor product title says 5.5 kg·cm. The manufacturer drawing says
4.4 kg·cm. This project uses the drawing value.

## Driver module

Source: `../datasheets/Trinamic-TMC2209-datasheet-rev1.09.pdf` and
`../datasheets/Pinout-of-Circuit-TMC2209.png`.

The module is a BIGTREETECH TMC2209 V1.3. It uses the A4988 StepStick pinout.

| Item | Value |
|---|---|
| Motor supply (VS) | 4.75 V to 28 V |
| Logic supply (VIO) | 3.3 V |
| Sense resistors | 0.11 Ω, two |
| Continuous current | 1.4 A RMS |
| Peak current | 2.5 A |
| Interface | STEP, DIR, EN, UART |

The module has these items on the board. The schematic does not add them.

- Charge pump capacitors.
- 5 V regulator and its capacitors.
- VREF potentiometer.
- 20 kΩ pull-up on EN.
- 20 kΩ pull-down on CLK.
- 20 kΩ pull-down on PDN_UART.
- 20 kΩ pull-downs on MS1 and MS2.

## Connections

| WeAct pin | Board pad | Module pin | Net |
|---|---|---|---|
| PA0 | A0 | 15 STEP | STEP |
| PA1 | A1 | 16 DIR | DIR |
| PA4 | A4 | 9 EN | EN |
| PA2 | A2 | 12 RX through R1 | PDN_UART |
| PA3 | A3 | 12 RX | PDN_UART |
| PB0 | B0 | 10 MS1 | MS1 |
| PB1 | B1 | 11 MS2 | MS2 |
| PB10 | B10 | J2-2 DIAG | DIAG |
| PB11 | B11 | J2-1 INDEX | INDEX |
| 3V3 | 3V3 | 2 VIO | +3V3 |
| GND | GND | 1, 7 GND | GND |

Motor connections:

| Motor wire | Motor connector J3 | Module pin |
|---|---|---|
| Red, A+ | 1 | 5 A1 |
| Green, A− | 2 | 6 A2 |
| Yellow, B+ | 3 | 4 B1 |
| Blue, B− | 4 | 3 B2 |

If the motor turns the wrong way, swap A1 and A2. Do not swap one wire inside
a coil pair.

## Current setting

The module uses two 0.11 Ω sense resistors. The TMC2209 datasheet gives this
formula for the RMS coil current in standalone mode:

```
I_RMS = 325 mV / (R_SENSE + 20 mΩ) × 1/√2 × VREF / 2.5 V
```

For R_SENSE = 0.11 Ω:

```
I_RMS = 0.707 × VREF
```

Set the VREF potentiometer to 1.68 V. This gives 1.19 A RMS.

The motor is rated 1.68 A per phase. The compiled reference in this folder
recommends 0.707 × I_rated for a chopper driver. This value also stays below
the 1.4 A RMS module rating.

Do not set VREF above 2.37 V (1.68 A RMS) unless the motor case stays below
80 °C. Measure VREF at TP2.

## Supply

Use a 24 V supply. This value is inside the module range and gives good
torque at speed.

C1 is a 100 µF low-ESR capacitor. C2 is a 100 nF capacitor. Place C1 near the
module VS pin. The TMC2209 datasheet recommends at least 100 µF near the
driver.

## UART

The UART uses one wire. The datasheet circuit is in Figure 4.1.

- MCU TX (PA2) drives the line through R1, a 1 kΩ resistor.
- MCU RX (PA3) connects to the same line.
- The module RX pin is PDN_UART.

Module settings:

- Set `GCONF.pdn_disable = 1`.
- Use 8 data bits, no parity.
- Use a baud rate from 9 kBd to fCLK/16.
- The node address is 0, because MS1 and MS2 are low.

The module TX pin (13) is not connected. R10 on the module is not fitted, so
the TX pin is isolated from PDN_UART. Use pin 12 for both directions.

## Socket

The socket is two 1×8 female headers. Use 2.54 mm pitch. Set the row spacing to
15.24 mm (0.6 in).

The module orientation:

- Pin 1 is GND at the bottom right.
- Pin 9 is EN at the top left.
- Pin 8 is VS at the top right.
- Pin 16 is DIR at the bottom left.

The module also has a 1×3 aux header J2. The order is INDEX, DIAG, VREF.

## Checks

Run the electrical rules check:

```sh
cd hardware
kicad-cli sch erc --severity-all NEMA17-TMC2209.kicad_sch
```

The current schematic reports 0 errors and 0 warnings.

Export a PDF:

```sh
cd hardware
kicad-cli sch export pdf -o NEMA17-TMC2209.pdf NEMA17-TMC2209.kicad_sch
```

## Limits

- The WeAct board pinout comes from the WeAct GitHub repository. This folder
  has no STM32G4 datasheet.
- The U1 symbol shows only the header pins that this design uses. Read the
  silkscreen name in brackets. For example, `PA0/A0` is the pad marked `A0`.
- The schematic has no reverse polarity protection and no overvoltage
  protection.
- The current values are calculated from datasheet formulas. Measure the real
  current before you run the motor for a long time.
- Connect the motor before you apply VM. Do not hot-plug the motor.
