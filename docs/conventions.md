# Conventions

These rules keep the repository consistent. Apply them to new files and new
designs.

## File naming

- Use lowercase words with hyphens for directories: `axis-tmc2209-spin`.
- Use the vendor name and the part number for datasheets: `Leison-17HS-series.pdf`.
- Keep the revision in the file name when the vendor gives one: `Trinamic-TMC2209-datasheet-rev1.09.pdf`.
- Use `.md` for text, `.pdf` for documents, `.png` for images, and `.csv` for tables.
- Do not use spaces in new file names. The JK42HS48 drawing is an exception because it came with that name.

## Net naming

Use one name for each signal. Add the axis letter as a suffix.

| Signal | Single axis | Axis A | Axis B |
|---|---|---|---|
| Step pulse | `STEP` | `STEP_A` | `STEP_B` |
| Direction | `DIR` | `DIR_A` | `DIR_B` |
| Enable | `EN` | `EN_A` | `EN_B` |
| UART | `PDN_UART` | `UART_A` | `UART_B` |

Use uppercase letters for net names. Put the power nets in the standard form:
`+24V`, `+5V`, `+3V3`, and `GND`.

## Power

- The motor supply is 24 V. Use `+24V` and `GND`.
- The TMC2209 logic supply is 3.3 V. Connect VIO to `+3V3`.
- The TB6600 opto inputs need 5 V. Connect the signal side to `+5V`.
- Connect all grounds together at one point.
- Do not power a motor from the 3.3 V regulator.
- Put a 100 µF or larger low-ESR capacitor near each driver supply pin.

## Datasheet intake

1. Download the file from the publisher when possible.
2. Check the page count and open the file.
3. Add a row to `datasheets/SOURCES.md`.
4. Record the publisher, the URL, the page count, and the SHA-256.
5. Note any change, such as a page extract or an image conversion.
6. Regenerate `datasheets/SHA256SUMS.txt`.
7. Do not edit a vendor PDF. If you must crop it, make a new file and note the change.

## KiCad rules

- Put shared symbols in `hardware/kicad/lib/`.
- Use one KiCad project for each board or axis. Put the project in `hardware/kicad/<project>/`.
- Keep the project local symbol table. Point it at `../lib/` with `${KIPRJMOD}`.
- Run ERC before you export a PDF.
- Export the PDF into the project directory.
- Do not commit backup files or local settings. The `.gitignore` file covers them.

## Firmware rules

- Use one PlatformIO project for each machine or axis.
- Put the project in `firmware/<machine-or-axis>-<driver>/`.
- Keep the pin map in one header or one config block.
- Keep the driver layer separate from the motion layer.
- Put shared code in `firmware/lib/` when the second project starts.
- Do not copy a driver layer into a second project. Move it to `firmware/lib/`.
- Set the driver current before you enable the driver.

## Safety

- Connect the motor before you apply motor power.
- Set the current before you enable the driver.
- Do not hot-plug the motor. An open coil can damage the driver.
- Disconnect the 24 V supply before you change a wire.
- Keep the driver disabled while you connect or disconnect the motor.
- Fit a heatsink on the driver module.
- Stop the test if the motor stalls, vibrates, or makes a loud noise.
- Measure the coil current before a long run.
