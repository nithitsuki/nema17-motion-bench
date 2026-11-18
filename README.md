# NEMA 17 motion bench

This repository is the catch-all for NEMA 17 motor experiments. It holds the
source documents, the KiCad designs, and the firmware for each bench setup.

## Current setup

| Item | Part |
|---|---|
| Motor | JK42HS48-1684-03F, 1.8°, 1.68 A per phase, 48 mm body |
| Driver | BIGTREETECH TMC2209 V1.3, A4988-style StepStick pinout |
| Controller | WeAct Studio STM32G474CEU6 "Long" core board |
| Supply | 24 V DC |
| Motor current | 1.19 A RMS (VREF 1.68 V) |

## Repository map

| Path | Contents |
|---|---|
| [`datasheets/`](datasheets/) | Manufacturer PDFs, source register, checksums |
| [`hardware/`](hardware/) | KiCad schematic, shared symbols, board pinouts |
| [`firmware/`](firmware/) | PlatformIO projects |
| [`docs/`](docs/) | Architecture, roadmap, conventions, driver notes |

## Quick start

1. Read the [schematic PDF](hardware/kicad/axis-tmc2209/NEMA17-TMC2209.pdf).
2. Read the [firmware README](firmware/axis-tmc2209-spin/README.md).
3. Follow the [flash steps](firmware/axis-tmc2209-spin/README.md#flash-over-usb-dfu).

## Roadmap

- [Phase 2: TB6600 module](docs/roadmap.md#phase-2-tb6600-module).
- [Phase 3: second motor](docs/roadmap.md#phase-3-second-motor).
- [Phase 4: CoreXY](docs/roadmap.md#phase-4-corexy).

## Sources and checks

The source URL and the SHA-256 for each document are in
[`datasheets/SOURCES.md`](datasheets/SOURCES.md).

Check the files:

```sh
cd datasheets
sha256sum -c SHA256SUMS.txt
```
