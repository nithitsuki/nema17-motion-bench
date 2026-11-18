# NEMA 17 datasheet library

This directory holds a set of manufacturer datasheets for NEMA 17 stepper
motors. It also holds one compiled reference document.

The bench motor is the JK42HS48-1684-03F. The library also covers the common
NEMA 17 families, so you can try other motors. Use the identification guide
in the reference document to find the sheet that matches your motor.

## Categories

| Folder | Contents |
|---|---|
| [`motors/nema17/`](motors/nema17/) | Motor drawings, catalogues, torque curves, compiled reference, CSV |
| [`drivers/tmc2209/`](drivers/tmc2209/) | TMC2209 IC datasheet, evaluation boards, BIGTREETECH files |
| [`drivers/tb6600/`](drivers/tb6600/) | TB6600HG datasheet, application note, 4 A module manual |
| [`drivers/b1206/`](drivers/b1206/) | B1206 label data and vendor photo |
| [`mcu/weact-stm32g474ceu6/`](mcu/weact-stm32g474ceu6/) | WeAct board schematic, STM32G474xE datasheet |
| [`standards/`](standards/) | NEMA ICS 16 flange 17 excerpt |

## Start here

1. Read [`motors/nema17/NEMA17-COMPREHENSIVE-DATASHEET.md`](motors/nema17/NEMA17-COMPREHENSIVE-DATASHEET.md).
2. Find your motor in the comparison table.
3. Open the matching PDF in [`motors/nema17/`](motors/nema17/).
4. Check the original file against [`SOURCES.md`](SOURCES.md).

## Motor files (motors/nema17/)

The compiled reference is the fastest way to compare models. The CSV holds
the same comparison table in machine-readable form.

| File | Coverage |
|---|---|
| `NEMA17-COMPREHENSIVE-DATASHEET.md` | Frame data, comparison tables, wiring, driver setup, selection guide |
| `nema17-specs.csv` | Comparison table as CSV |
| `Leison-17HS-series.pdf` | Full 17HS table, 20 mm to 63 mm, 1.8° |
| `MotionKing-17HS-series-catalog.pdf` | Cross-check of the 17HS table, extra 6-lead models |
| `Handson-17HS4401S.pdf` | 17HS4401S, dimensions, body-length chart |
| `StepperOnline-17HS19-2004S1.pdf` | 48 mm, 2.0 A, 59 Ncm |
| `StepperOnline-17HS19-2004S1-torque-curve.pdf` | Speed-torque curve for the 2004S1 |
| `StepperOnline-17HS08-1004S-pancake.pdf` | 20 mm pancake, 1.0 A |
| `Pololu-2267-SY42STH38-1684A.pdf` | 38 mm, 1.68 A, 4 leads |
| `Pololu-1200-SY42STH47-1206A.pdf` | 48 mm, 1.2 A, 6 leads |
| `Trinamic-QSH4218-manual.pdf` | Four models, torque curves, driver theory |
| `LDO-42STH-series-info-sheet.pdf` | Wide winding table, 25 mm to 60 mm |
| `LDO-42STH48-2504AC-drawing.pdf` | 2.5 A, 0.55 Nm drawing |
| `Moons-MS17HA-MS17HD-series.pdf` | 0.9° and 1.8° families, 25 mm to 63 mm |
| `LinEngineering-4209-0.9deg.pdf` | 0.9°, series and parallel windings |
| `Adafruit-324-datasheet.pdf` | 34 mm, 0.35 A, Arduino shield motor |
| `JK42HS48-1684-03F NEMA17 5.5 kg-cm Stepper Motor - D-Type Shaft-Nema-17.pdf` | Bench motor drawing, 1.68 A, 4.4 kg·cm |

## Driver files

### TMC2209 (drivers/tmc2209/)

| File | Coverage |
|---|---|
| `Trinamic-TMC2209-datasheet-rev1.09.pdf` | Current IC datasheet, register map, UART protocol |
| `Trinamic-TMC2209-datasheet-rev1.05.pdf` | Older revision, quoted by some board vendors |
| `Trinamic-TMC2209-SilentStepStick-manual-rev1.2.pdf` | Pololu-style 2x8 module, schematic and BOM |
| `Trinamic-TMC2209-BOB-manual-rev1.0.pdf` | 2x10 breakout board |
| `Trinamic-TMC2209-EVAL-user-manual-rev1.0.pdf` | Evaluation board |
| `BTT-TMC2209-V1.3-schematic.pdf` | BIGTREETECH V1.3 board schematic |
| `BTT-TMC2209-V1.3-pinout.png` | BIGTREETECH V1.3 pin labels |

The TMC2209 uses 3.3 V logic. It has a single-wire UART and StealthChop.
The current design uses this driver.

### TB6600 (drivers/tb6600/)

| File | Coverage |
|---|---|
| `Toshiba-TB6600HG-datasheet-2016-06-10.pdf` | TB6600HG chip, ratings, truth tables |
| `Toshiba-TB6600HG-application-note-AKX00354.pdf` | Application circuits and thermal data |
| `Handson-TB6600-4A-module-manual.pdf` | 4 A module, wiring diagram, DIP tables |

The TB6600 module uses 5 V logic. It sets current and microsteps with DIP
switches. It has no UART. See [`../docs/drivers/tb6600.md`](../docs/drivers/tb6600.md).

### B1206 (drivers/b1206/)

| File | Coverage |
|---|---|
| `README.md` | Label data, 8 DIP switches, current table, terminal list |
| `B1206-label.png` | Vendor photo of the label |

The B1206 module uses opto-isolated inputs, 5 V typical. It sets current with SW6 to SW8 and
step mode with SW3. It has full-step and half-step only. It has no UART. No
manufacturer PDF exists. See [`../docs/drivers/b1206.md`](../docs/drivers/b1206.md).

## MCU files

The WeAct folder holds the V1.0 "Long" board schematic and the
STM32G474xE datasheet, DS12288. The pin map is in
[`../hardware/pinouts/weact-stm32g474ceu6.md`](../hardware/pinouts/weact-stm32g474ceu6.md).

## Coverage

| Axis | Covered values |
|---|---|
| Step angle | 1.8° (200 steps/rev) and 0.9° (400 steps/rev) |
| Body length | 20 mm to 63 mm |
| Rated current | 0.16 A to 2.8 A per phase |
| Holding torque | 10 Ncm to 88 Ncm |
| Windings | 4-lead bipolar, 6-lead unipolar/bipolar |
| Extras | Torque curves, dimension drawings, NEMA ICS 16 flange excerpt |

## Adding a datasheet

1. Select the folder for the document category.
2. Add the file with the naming rules in [`../docs/conventions.md`](../docs/conventions.md).
3. Add a row to [`SOURCES.md`](SOURCES.md). Include the publisher, URL, page count, and SHA-256.
4. Regenerate the checksum file from this directory.

```sh
find . -type f \( -name '*.pdf' -o -name '*.png' \) | sort | xargs -d '\n' sha256sum > SHA256SUMS.txt
```

## Integrity check

```sh
cd datasheets
sha256sum -c SHA256SUMS.txt
```

## Limits

- These files are manufacturer documents. This project did not measure a motor.
- Motor vendors change parts without notice. Check the drawing for your exact batch.
- Wire colours are not standardized. Measure the coil pairs before you connect a driver.
- A document can be out of date. Trust the drawing for your batch, not a product page.
