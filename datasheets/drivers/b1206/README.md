# B1206 stepper driver

## Status

No manufacturer datasheet was found for this module. It is a generic
two-phase driver sold under several brand names. This page records the data
from the product label and from the vendor listings. The label photo in this
folder is the primary source.

## Summary

| Item | Value |
|---|---|
| Type | Two-phase bipolar stepper driver |
| Peak output current | 6.0 A |
| Current range | 1.9 A to 6.0 A |
| Motor supply | 20 V to 120 V DC (vendor listings) |
| Inputs | Opto-isolated: Pul, Dir, Ena |
| Microsteps | 1 and 1/2 step only |
| DIP switches | 8 (SW1 to SW8) |
| UART | None |
| Feedback | Power LED and Error LED only |

The label does not state the supply voltage or the logic voltage. Check the
label and the listing for your unit. The vendor pages disagree on the supply
range. The sys-motor feature list says 16 V to 60 V. The product title and
the other listings say 20 V to 120 V.

## DIP switches

The label shows eight switches, SW1 to SW8. The label describes SW2, SW3, and
SW6 to SW8. SW1, SW4, and SW5 have no function printed on the label.

### SW2: pulse mode

| SW2 | Mode |
|---|---|
| ON | Two pulse (CW and CCW inputs) |
| OFF | Single pulse (STEP and DIR inputs) |

Use OFF for the STEP/DIR firmware in this repository.

### SW3: step mode

| SW3 | Mode | Steps/rev for a 1.8° motor |
|---|---|---|
| ON | 1/2 step | 400 |
| OFF | 1 step | 200 |

### SW6 to SW8: current

| SW6 | SW7 | SW8 | Current |
|---|---|---|---:|
| OFF | OFF | OFF | 1.9 A |
| ON | OFF | OFF | 2.4 A |
| OFF | ON | OFF | 3.0 A |
| ON | ON | OFF | 3.6 A |
| OFF | OFF | ON | 4.2 A |
| ON | OFF | ON | 4.8 A |
| OFF | ON | ON | 5.7 A |
| ON | ON | ON | 6.0 A |

The lowest setting is 1.9 A. The JK42HS48-1684-03F is rated 1.68 A. This
driver cannot set a current below the motor rating. Use it with a larger
motor, such as a NEMA 23 or NEMA 34.

## Terminals

The label lists these terminals from top to bottom:

| Terminal | Function |
|---|---|
| V+ | Motor supply positive |
| GND | Motor supply ground |
| A+ | Coil A positive |
| A− | Coil A negative |
| B+ | Coil B positive |
| B− | Coil B negative |
| Ena− | Enable, negative side |
| Ena+ | Enable, positive side |
| Pul− | Step pulse, negative side |
| Pul+ | Step pulse, positive side |
| Dir− | Direction, negative side |
| Dir+ | Direction, positive side |

The negative terminal comes first in each signal pair. This is the opposite
order from the TB6600 module.

## Sources

- QYSMT product page, product photos and current switch note:
  <https://www.qysmt.in/products/b1206-stepper-drive>
- sys-motor product page, title and feature list:
  <https://www.sys-motor.com/show.aspx?id=1399>
- Project brief, 2026-11-18: two-phase bipolar, 20 V to 120 V DC, up to 6 A.

The label photo `B1206-label.png` comes from the QYSMT product page.

## Limits

- There is no manufacturer PDF. The data comes from one label photo and
  reseller pages.
- The supply range is not confirmed. Measure your unit before you apply
  power.
- The functions of SW1, SW4, and SW5 are unknown. Do not change them from the
  factory setting until you confirm them.
- The module has no current readback and no fault register.
