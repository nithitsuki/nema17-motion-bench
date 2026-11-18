# NEMA 17 datasheet library

This directory holds a set of manufacturer datasheets for NEMA 17
stepper motors. It also holds one compiled reference document.

No motor part number was given for this project. The library therefore
covers the common NEMA 17 families. Use the identification guide in the
reference document to find the sheet that matches your motor.

## Project

The repository also holds a complete single-axis driver design:

| Path | Contents |
|---|---|
| `hardware/` | KiCad schematic, PDF, and project symbols for the NEMA 17 + TMC2209 + WeAct STM32G474CEU6 axis |
| `firmware/` | PlatformIO firmware for STEP/DIR control and TMC2209 UART setup |
| `board/` | WeAct STM32G474CEU6 pinout reference |

## Start here

1. Read [`NEMA17-COMPREHENSIVE-DATASHEET.md`](NEMA17-COMPREHENSIVE-DATASHEET.md).
2. Find your motor in the comparison table.
3. Open the matching PDF in [`datasheets/`](datasheets/).
4. Check the original file against [`datasheets/SOURCES.md`](datasheets/SOURCES.md).

## Files

| File | Contents |
|---|---|
| `NEMA17-COMPREHENSIVE-DATASHEET.md` | Compiled reference: frame data, comparison tables, wiring, driver setup, selection guide |
| `nema17-specs.csv` | The comparison table in machine-readable form |
| `datasheets/` | 14 manufacturer datasheets, 1 standard excerpt, checksums |
| `datasheets/SOURCES.md` | Source URL, publisher, page count, and SHA-256 for each file |
| `datasheets/SHA256SUMS.txt` | Checksums for integrity checks |

## Coverage

| Axis | Covered values |
|---|---|
| Step angle | 1.8° (200 steps/rev) and 0.9° (400 steps/rev) |
| Body length | 20 mm to 63 mm |
| Rated current | 0.16 A to 2.8 A per phase |
| Holding torque | 10 Ncm to 88 Ncm |
| Windings | 4-lead bipolar, 6-lead unipolar/bipolar |
| Extras | Torque curves, dimension drawings, NEMA ICS 16 flange excerpt |

## Integrity check

```sh
cd datasheets
sha256sum -c SHA256SUMS.txt
```

## Limits

- These files are manufacturer documents. This project did not measure a motor.
- Motor vendors change parts without notice. Check the drawing for your exact batch.
- Wire colours are not standardized. Measure the coil pairs before you connect a driver.
