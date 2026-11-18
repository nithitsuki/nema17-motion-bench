# Roadmap

The bench moves from one axis to a CoreXY machine in four phases. Phase 1 is
done. Phases 2, 3, and 4 are not implemented.

## Phases

| Phase | Scope | Driver | Status |
|---|---|---|---|
| 1 | Single axis, STEP/DIR and UART | TMC2209 | Done |
| 2 | TB6600 module, 5 V logic, DIP settings, no UART | TB6600 | Not implemented |
| 3 | Second motor, second TMC2209, separate UART address or bus | TMC2209 | Not implemented |
| 4 | CoreXY, two motors, coordinated moves, homing, endstops, planner | TMC2209 | Not implemented |

## Phase 1: single axis

**Goal:** Turn one motor at a set speed and direction. Set the driver current
and microsteps over UART.

**Hardware:** JK42HS48-1684-03F motor, BIGTREETECH TMC2209 V1.3 module, WeAct
STM32G474CEU6 board, 24 V supply.

**Firmware work:** Done. The project is in `firmware/axis-tmc2209-spin/`. It
sets the TMC2209 registers, reads the driver version, and generates STEP
pulses on PA0.

**Open questions:** None for the current setup. The VREF value is a calculated
value. Measure the coil current before a long run.

## Phase 2: TB6600 module

**Goal:** Drive one motor with a TB6600 module. Set current and microsteps
with the DIP switches.

**Hardware:** TB6600 4 A module, 24 V supply, 5 V logic level on the signal
side. The WeAct board has a 5 V pin.

**Firmware work:** Use the same STEP/DIR code with a different pin map. Add a
build flag or a new project for the TB6600. Do not send UART commands. Read
the DIP settings in the firmware config.

**Open questions:** Does the 3.3 V GPIO sink enough current in common-anode
mode? Measure the input current. Which current setting suits the
JK42HS48-1684-03F? See `docs/drivers/tb6600.md`.

**Other option:** The B1206 module is also available. It has a 20 V to 120 V
supply range and a 1.9 A to 6.0 A current range. Its minimum current is
1.9 A, so it suits a NEMA 23 or NEMA 34, not the JK42HS48-1684-03F. It has
full-step and half-step only. See `docs/drivers/b1206.md`.

## Phase 3: second motor

**Goal:** Drive two motors from one board. Keep a separate current and
steps/rev value for each motor.

**Hardware:** A second TMC2209 module and a second motor. The WeAct board has
enough GPIO for STEP, DIR, and EN. Use a second UART, or set MS1 and MS2 to a
different node address and share the bus.

**Firmware work:** Add a driver instance for motor B. Add a UART transport
that can select a node address. Store steps/rev, current, and direction for
each motor. Do not hard-code one motor profile.

**Open questions:** One UART bus or two? A shared bus needs a unique node
address for each driver. Two buses use more pins but remove the address
limit.

## Phase 4: CoreXY

**Goal:** Move a tool head in X and Y with two belts and two motors.

**Hardware:** Two motors, two TMC2209 modules, two endstops, and a rigid
frame. The motor current and the steps/rev can differ between A and B. A
mixed build can use one TMC2209 and one TB6600. The motion layer only needs
STEP and DIR, so the driver type can differ between A and B.

**Firmware work:** Add a motion planner, coordinated moves, homing, and
endstop inputs. Convert a Cartesian move to motor A and motor B steps. Keep
the motion layer separate from the driver layer. The driver layer sends STEP
pulses and sets registers. The motion layer computes the step counts and the
timing.

**Open questions:** What is the belt pitch and the pulley tooth count? What is
the travel limit for each axis? Which endstop inputs are free? Does the
planner need look-ahead for the target speed?

## CoreXY notes

The two belt motors use these equations:

```
A = x + y
B = x - y
```

A move in X turns both motors in the same direction. A move in Y turns the
motors in opposite directions. A diagonal move turns them at different rates.

The two motors may be different models. Keep these values for each motor:

- Steps per revolution.
- Motor current.
- Direction sign.

Keep the motion layer separate from the driver layer. The motion layer works
in steps and time. The driver layer works in pins and registers. A change to a
driver must not change the planner.
