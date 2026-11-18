# Firmware

This directory holds one PlatformIO project for each machine or axis. The
current project is `axis-tmc2209-spin/`.

## Index

| Project | Contents |
|---|---|
| [`axis-tmc2209-spin/`](axis-tmc2209-spin/) | One NEMA 17 motor on a TMC2209, STEP/DIR and UART |

## Build, flash, and monitor

Run these commands from the repository root:

```sh
cd firmware/axis-tmc2209-spin
pio run
pio run -t upload
pio device monitor
```

The upload uses the ROM DFU bootloader. Hold **BOOT0**, tap **NRST**, and
release **BOOT0** before you run `pio run -t upload`. The full steps are in
[`axis-tmc2209-spin/README.md`](axis-tmc2209-spin/README.md#flash-over-usb-dfu).

## Behaviour

The firmware holds the driver disabled at boot. It sets the TMC2209 over the
single-wire UART at 115200 baud and reads the driver version. It then enables
the driver and starts STEP pulses at 3200 Hz, which is 1 rev/s at 3200
steps/rev. The console accepts single-key commands to start, stop, change the
speed, change the direction, and read the driver status. The blue LED on PC6
blinks every 500 ms.

## Future

When the CoreXY project starts, put shared code in `firmware/lib/`. Shared
code includes the TMC2209 register layer, the UART transport, and the motion
planner.

The rule is one PlatformIO project for each machine or axis. Do not put a
second `platformio.ini` at this level.
