# Architecture

## Purpose and scope

This document describes the layout of the repository. It covers the four
layers and the rules that connect them. It does not describe the electrical
design. The hardware README and the schematic do that.

## Layers

| Layer | Path | Role |
|---|---|---|
| Datasheets | `datasheets/` | Primary sources. Manufacturer files, source register, checksums. |
| Hardware | `hardware/` | KiCad projects, shared symbols, board pinouts. |
| Firmware | `firmware/` | PlatformIO projects, one per machine or axis. |
| Docs | `docs/` | Decisions, conventions, and driver notes. |

A lower layer does not depend on a higher layer. A datasheet does not link to
firmware. Firmware links to the pins in the hardware layer.

## Naming rules

| Item | Pattern | Example |
|---|---|---|
| Datasheet | `datasheets/<category>/<family>/` | `datasheets/drivers/tmc2209/` |
| KiCad project | `hardware/kicad/<project>/` | `hardware/kicad/axis-tmc2209/` |
| Firmware project | `firmware/<machine-or-axis>-<driver>/` | `firmware/axis-tmc2209-spin/` |

Use lowercase words with hyphens for directories. Use the vendor file name
for datasheets. Keep the revision in the file name when the vendor does.

## Data flow

The design flows in one direction:

1. The datasheet gives the part ratings and the pin functions.
2. The schematic uses those ratings to select parts and nets.
3. The firmware uses the net names and the pin map.

When a value changes, change the source first. Update the schematic second.
Update the firmware last. Record the reason in `docs/`.

## Shared code

The current repository has one firmware project. Shared code will go in
`firmware/lib/` when the second project starts. The first candidates are the
TMC2209 register layer and the UART transport.

## How to add a part

### Add a motor

1. Put the drawing and the catalogue in `datasheets/motors/<family>/`.
2. Add a row to `datasheets/SOURCES.md`.
3. Add the model to the compiled reference and the CSV.
4. Regenerate `datasheets/SHA256SUMS.txt`.

### Add a driver

1. Put the IC datasheet and the module files in `datasheets/drivers/<driver>/`.
2. Add a row to `datasheets/SOURCES.md`.
3. Add a note in `docs/drivers/` when the module has special rules.
4. Add the socket and the nets to the schematic.

### Add a board

1. Put the schematic and the MCU datasheet in `datasheets/mcu/<board>/`.
2. Write the pin map in `hardware/pinouts/`.
3. Add the board symbols to `hardware/kicad/lib/`.
4. Create one KiCad project in `hardware/kicad/<project>/`.
5. Create one firmware project in `firmware/<machine>-<driver>/`.
