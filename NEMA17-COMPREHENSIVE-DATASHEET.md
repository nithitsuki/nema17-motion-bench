# NEMA 17 stepper motor: comprehensive datasheet reference

Compiled on 2026-11-12. All values come from the manufacturer files in
[`datasheets/`](datasheets/). The source file for each value is named in
the section.

## 1. Scope

NEMA 17 is a frame size, not a motor model. Two motors with the NEMA 17
label can differ in length, current, torque, winding, and shaft.

This document covers the common NEMA 17 families:

- 17HS series from MotionKing, Leison, and Handson (the low-cost 3D-printer
  and CNC motors, including 17HS4401).
- StepperOnline 17HS19-2004S1 and 17HS08-1004S.
- Pololu / SOYO 42STH38 and 42STH47.
- Trinamic QSH4218 (1 A and 2.8 A versions).
- LDO 42STH series and LDO-42STH48-2504AC.
- MOONS' MS17HA (0.9°) and MS17HD (1.8°) series.
- Lin Engineering 4209 (0.9°).
- Adafruit 324 / XY42STH34-0354A.

The document does not cover closed-loop motors, integrated encoder
motors, or AC steppers.

## 2. NEMA 17 frame data

### 2.1 The interface that stepper makers use

These values agree across the included drawings (Leison, StepperOnline,
Pololu, LDO, MOONS', Trinamic):

| Item | Value |
|---|---|
| Flange, square | 42.3 mm maximum |
| Mounting hole spacing | 31.0 mm ± 0.1 mm square |
| Mounting holes | 4 × M3, 4.5 mm deep minimum |
| Pilot (register) diameter | 22 mm, tolerance 0 to −0.052 mm |
| Shaft diameter | 5 mm, tolerance 0 to −0.012 mm |
| Shaft length | 24 mm typical |
| D-cut | 15 mm to 20 mm, 0.5 mm deep |
| Step angle | 1.8° (200 steps/rev) or 0.9° (400 steps/rev) |

The pilot fits a 22 mm bore. The four M3 screws pass through the mounting
plate and thread into the motor face. Use screws that engage 3 mm to
4.5 mm. A screw that is too long can damage the winding.

### 2.2 A warning about the "NEMA 17" name

NEMA ICS 16-2001 defines an inch "flange 17" pattern. That pattern is
not the pattern above:

| Item | ICS 16 flange 17 | Common stepper "NEMA 17" |
|---|---|---|
| Flange square | 1.725 in (43.8 mm) | 42.3 mm |
| Bolt circle | 1.7 in (43.18 mm) | 31.0 mm square |
| Pilot | 0.8661 in (22 mm) | 22 mm |
| Thread | 4-40 UNC | M3 |

Source: `NEMA-ICS16-2001-flange-17-excerpt.pdf`, Table 4.

The stepper industry uses the 42.3 mm / 31 mm / M3 pattern and keeps the
"NEMA 17" nickname. Treat the name as a faceplate size only. Always use
the motor drawing for the mounting pattern.

## 3. Identify the motor you have

Do these steps before you select a driver.

1. Read the label. Look for a model such as 17HS4401, 17HS19-2004S1, or
   QSH4218-51-10-049.
2. Measure the body length, not the shaft. Common lengths are 20, 25,
   28, 34, 38, 40, 48, and 60 mm. Body length is the fastest way to narrow
   the model.
3. Count the leads. Four leads are bipolar. Six leads are unipolar or
   bipolar. Five leads are unipolar only.
4. Measure the resistance between each pair of leads with a multimeter.
   A coil pair has a low, equal resistance. Compare the value with the
   tables below.
5. Measure the shaft. Most NEMA 17 motors have a 5 mm shaft with a D-cut.
   Some have a round shaft, a dual shaft, or a threaded rod.

If the label is missing, use the resistance and body length together.
Two motors with the same body length can have different windings.

## 4. Comparison tables

### 4.1 1.8° motors (200 steps/rev)

`I` is the rated current per phase. `R` and `L` are per phase. Torque is
holding torque. `Leads` is the lead count. `Mass` is approximate.

| Model | Body (mm) | I (A) | R (Ω) | L (mH) | Torque (Ncm) | Leads | Mass (g) | Source file |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| 17HS0410 | 20 | 0.8 | 3.8 | 4.5 | 10 | 4 | 120 | Leison |
| 17HS08-1004S | 20 | 1.0 | 3.5 | 4.5 | 13 | 4 | 150 | StepperOnline |
| 17HS2408 | 28 | 0.6 | 8.0 | 10 | 12 | 4 | 150 | Leison |
| QSH4218-35-10-027 | 33.5 | 1.0 | 5.3 | 6.6 | 27 | 4 | 220 | Trinamic |
| 17HS3401 | 34 | 1.3 | 2.4 | 2.8 | 28 | 4 | 220 | Leison |
| 17HS3410 | 34 | 1.7 | 1.2 | 1.8 | 28 | 4 | 220 | Leison |
| 17HS3430 | 34 | 0.4 | 30 | 35 | 28 | 4 | 220 | MotionKing |
| 17HS3630 | 34 | 0.4 | 30 | 18 | 21 | 6 | 220 | MotionKing |
| 17HS3616 | 34 | 0.16 | 75 | 40 | 14 | 6 | 220 | MotionKing |
| XY42STH34-0354A | 34 | 0.35 | 34 | 33 | 15.7 | 4 | 220 | Adafruit |
| MS17HD4P4100 | 34.3 | 1.0 | 4.2 | 7.5 | 33 | 4 | 210 | MOONS' |
| SY42STH38-1684A | 38 | 1.68 | 1.65 | 3.2 | 36 | 4 | 285 | Pololu |
| QSH4218-41-10-035 | 38 | 1.0 | 4.5 | 7.5 | 35 | 4 | 280 | Trinamic |
| MS17HD2P4100 | 39.8 | 1.0 | 3.9 | 8.9 | 48 | 4 | 280 | MOONS' |
| 17HS4401 | 40 | 1.7 | 1.5 | 2.8 | 40 | 4 | 280 | Leison |
| 17HS4401S | 40 | 1.7 | 1.5 | 2.8 | 43 | 4 | 280 | Handson |
| 17HS4402 | 40 | 1.3 | 2.5 | 5.0 | 40 | 4 | 280 | Leison |
| 17HS4602 | 40 | 1.2 | 3.2 | 2.8 | 28 | 6 | 280 | Leison |
| 17HS4630 | 40 | 0.4 | 30 | 28 | 28 | 6 | 280 | MotionKing |
| QSH4218-51-10-049 | 47 | 1.0 | 5.0 | 8.0 | 49 | 4 | 350 | Trinamic |
| QSH4218-47-28-040 | 47 | 2.8 | 0.5 | 0.6 | 40 | 4 | 350 | Trinamic |
| 17HS19-2004S1 | 48 | 2.0 | 1.4 | 3.0 | 59 | 4 | 400 | StepperOnline |
| 17HS8401 | 48 | 1.7 | 1.8 | 3.2 | 52 | 4 | 350 | Leison |
| 17HS8402 | 48 | 1.3 | 3.2 | 5.5 | 52 | 4 | 350 | Leison |
| 17HS8403 | 48 | 2.3 | 1.2 | 1.6 | 46 | 4 | 350 | Leison |
| 17HS8630 | 48 | 0.4 | 30 | 38 | 34 | 6 | 350 | Leison |
| SY42STH47-1206A | 48 | 1.2 | 3.3 | 2.8 | 31.1 | 6 | 365 | Pololu |
| LDO-42STH48-2504AC | 48 | 2.5 | 1.2 | 1.5 | 55 | 4 | 350 | LDO |
| MS17HD6P4100 | 48.3 | 1.0 | 4.9 | 11.5 | 63 | 4 | 360 | MOONS' |
| 17HS9403 | 60 | 2.3 | 1.4 | 2.5 | 70 | 4 | 480 | Leison |
| MS17HDBP4100 | 62.8 | 1.0 | 5.6 | 14.6 | 82 | 4 | 600 | MOONS' |
| 17HS6403 | 63 | 2.3 | 1.5 | 2.2 | 80 | 4 | 500 | Leison |

### 4.2 0.9° motors (400 steps/rev)

| Model | Body (mm) | I (A) | R (Ω) | L (mH) | Torque (Ncm) | Leads | Mass (g) | Source file |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| 4209S-01P | 34 | 1.33 | 2.4 | 4.6 | 22 | 4 | 200 | Lin |
| MS17HA4P4100 | 34.3 | 1.0 | 4.0 | 11.4 | 30 | 4 | 210 | MOONS' |
| 4209M-01P | 39.9 | 1.68 | 1.5 | 3.8 | 36 | 4 | 254 | Lin |
| MS17HA2P4100 | 39.8 | 1.0 | 4.0 | 9.7 | 42 | 4 | 280 | MOONS' |
| 4209L-01P | 48 | 1.70 | 1.9 | 5.3 | 44 | 4 | 318 | Lin |
| MS17HA6P4100 | 48.3 | 1.0 | 4.9 | 17.6 | 56 | 4 | 350 | MOONS' |

### 4.3 Unit notes

- `Ncm` is newton-centimetre. 1 Ncm = 0.01 Nm.
- 1 kg-cm = 9.807 Ncm.
- 1 oz-in = 0.706 Ncm.
- The "rated voltage" in a stepper datasheet is usually `I × R`. It is
  not a supply limit. Chopper drivers use a much higher supply.
- Some vendors give torque in kg-cm and some in Nm. The tables above are
  converted to Ncm and rounded to one decimal place.

## 5. Family details

### 5.1 17HS4401 and 17HS4401S (40 mm, 1.7 A)

This is the most common NEMA 17 motor in low-cost 3D printers and CNC
machines. The base model is 17HS4401. The "S" version adds a cable and
connector and is rated at 43 Ncm.

| Item | 17HS4401 | 17HS4401S |
|---|---|---|
| Step angle | 1.8° | 1.8° |
| Body length | 40 mm | 40 mm |
| Rated current | 1.7 A/phase | 1.7 A/phase |
| Phase resistance | 1.5 Ω ±10% | 1.5 Ω ±10% |
| Phase inductance | 2.8 mH ±20% | 2.8 mH ±20% |
| Holding torque | 40 Ncm min | 43 Ncm |
| Detent torque | 2.2 Ncm max | not stated |
| Rotor inertia | 54 g·cm² | 54 g·cm² |
| Leads | 4 | 4 |
| Mass | 280 g | 280 g |
| Shaft | 5 mm D, 24 mm | 5 mm D, 24 mm |
| Insulation | Class B | Class B |
| Dielectric strength | 500 VAC, 1 min | 500 VAC, 1 min |

Sources: `Leison-17HS-series.pdf`, `Handson-17HS4401S.pdf`,
`MotionKing-17HS-series-catalog.pdf`.

Handson gives a phase voltage of 2.6 V. That matches 1.7 A × 1.5 Ω.

The 17HS4401 is a good default for a 24 V system with a TMC2209 or
A4988-class driver. Set the driver to about 1.2 A RMS, not 1.7 A RMS.
See section 7.

### 5.2 StepperOnline 17HS19-2004S1 (48 mm, 2.0 A, 59 Ncm)

A common upgrade motor for 3D-printer X/Y axes.

| Item | Value |
|---|---|
| Step angle | 1.8° |
| Body length | 48 mm max |
| Rated voltage | 2.8 V |
| Rated current | 2.0 A/phase |
| Phase resistance | 1.40 Ω ±10% at 25 °C |
| Phase inductance | 3.0 mH ±20% at 1 kHz |
| Holding torque | 0.59 Nm (5.22 lb-in) |
| Step accuracy | ±5% non-accumulating |
| Rotor inertia | 82 g·cm² |
| Mass | 0.40 kg |
| Leads | 4, 1000 mm cable |
| Connector | Molex / Harwin 2.54 mm 4-pin |
| Insulation | Class B, 130 °C |
| Temperature rise | 80 °C max at rated current, 2 phases on |
| Ambient | −10 °C to +50 °C |

Source: `StepperOnline-17HS19-2004S1.pdf`. Torque curve:
`StepperOnline-17HS19-2004S1-torque-curve.pdf`.

Winding: Black A+, Green A−, Red B+, Blue B−.

The vendor product page lists 1.6 Ω, but the drawing and the electrical
table in the PDF list 1.40 Ω. Use the PDF value and measure your motor.

### 5.3 StepperOnline 17HS08-1004S (20 mm pancake, 1.0 A)

A short motor for extruders and light axes.

| Item | Value |
|---|---|
| Step angle | 1.8° |
| Body length | 20 mm |
| Rated voltage | 3.5 V |
| Rated current | 1.0 A/phase |
| Phase resistance | 3.5 Ω ±10% |
| Phase inductance | 4.5 mH ±20% |
| Holding torque | 0.13 Nm (1.15 lb-in) |
| Rotor inertia | 15 g·cm² |
| Mass | 0.15 kg |
| Leads | 4, 400 mm cable |
| Shaft | 5 mm D, 24 mm, 16.5 mm D-cut |

Source: `StepperOnline-17HS08-1004S-pancake.pdf`.

### 5.4 Pololu / SOYO 42STH38 and 42STH47

Pololu sells these as #2267 and #1200.

| Item | SY42STH38-1684A (#2267) | SY42STH47-1206A (#1200) |
|---|---|---|
| Step angle | 1.8° | 1.8° |
| Body length | 38 mm | 47 mm to 48 mm |
| Rated voltage | 2.8 V | 4 V |
| Rated current | 1.68 A | 1.2 A |
| Phase resistance | 1.65 Ω ±10% | 3.3 Ω ±10% |
| Phase inductance | 3.2 mH ±20% | 2.8 mH ±20% |
| Holding torque | 36 Ncm | 3.17 kg-cm (31.1 Ncm) |
| Detent torque | not stated | 200 g-cm |
| Rotor inertia | not stated | 68 g·cm² |
| Leads | 4 | 6 (unipolar or bipolar) |
| Mass | 285 g | 365 g |
| Insulation | Class B | Class B |
| Max radial force | 28 N at 20 mm | 28 N at 20 mm |
| Max axial force | 10 N | 10 N |

Sources: `Pololu-2267-SY42STH38-1684A.pdf`,
`Pololu-1200-SY42STH47-1206A.pdf`, and the Pololu product pages.

The #1200 has six leads. Use the black/green pair for coil A and the
red/blue pair for coil B in bipolar mode. Leave the yellow and white
centre taps open. In unipolar mode, connect the centre taps to the
supply.

### 5.5 Trinamic QSH4218 (1 A and 2.8 A)

A matched family with published torque curves and a detailed driver
application note. Use this manual when you need to calculate the supply
voltage or read a torque curve.

| Model | Body (mm) | I (A) | R (Ω) | L (mH) | Torque (Ncm) | Mass (kg) |
|---|---:|---:|---:|---:|---:|---:|
| QSH4218-35-10-027 | 33.5 | 1.0 | 5.3 | 6.6 | 27 | 0.22 |
| QSH4218-41-10-035 | 38 | 1.0 | 4.5 | 7.5 | 35 | 0.28 |
| QSH4218-51-10-049 | 47 | 1.0 | 5.0 | 8.0 | 49 | 0.35 |
| QSH4218-47-28-040 | 47 | 2.8 | 0.5 | 0.6 | 40 | 0.35 |

All models: 1.8°, 4 leads, ±5% step accuracy, 42.3 mm flange,
5 mm shaft, 20 mm D-cut, Class B, 500 VAC dielectric strength,
−20 °C to +50 °C ambient.

Winding: Black A, Green A−, Red B, Blue B−.

Source: `Trinamic-QSH4218-manual.pdf`.

Section 6.3 of that manual gives a supply-voltage rule of thumb:

- Minimum supply: 2 × nominal coil voltage.
- Optimum supply: 4 × to 22 × nominal coil voltage.
- Maximum supply: 25 × nominal coil voltage.

Nominal coil voltage is `I_RMS × R_coil`. The rule is useful for any
chopper-driven stepper, not only the QSH4218.

### 5.6 LDO 42STH series

LDO publishes a wide table of NEMA 17 windings from 25 mm to 60 mm. The
table is useful when you need a low-current or high-torque winding.

| Model | Body (mm) | I (A) | R (Ω) | L (mH) | Torque (kg-cm) | Leads | Mass (kg) |
|---|---:|---:|---:|---:|---:|---:|---:|
| LDO-42STH25-0404 | 25 | 0.4 | 24 | 36 | 1.7 | 4 | 0.15 |
| LDO-42STH33-1334 | 34 | 1.33 | 2.1 | 2.5 | 2.2 | 4 | 0.22 |
| LDO-42STH38-1684 | 40 | 1.68 | 1.65 | 3.2 | 3.6 | 4 | 0.28 |
| LDO-42STH47-1206 | 48 | 1.2 | 3.3 | 2.8 | 3.17 | 6 | 0.35 |
| LDO-42STH47-1684 | 48 | 1.68 | 1.65 | 2.8 | 4.4 | 4 | 0.35 |
| LDO-42STH60-1206 | 60 | 1.2 | 6 | 7 | 6.5 | 6 | 0.50 |

Source: `LDO-42STH-series-info-sheet.pdf`. The sheet also lists
6-lead versions and other windings.

The 38 series appears as 40 mm in the LDO table. Other LDO documents and
the Pololu drawing show the same motor at 38 mm. Measure the body before
you order a mount.

#### LDO-42STH48-2504AC

A high-current 48 mm motor used in Voron-class printers.

| Item | Value |
|---|---|
| Step angle | 1.8° |
| Body length | 48 mm |
| Rated voltage | 3.0 V |
| Rated current | 2.5 A/phase |
| Phase resistance | 1.2 Ω ±20% |
| Phase inductance | 1.5 mH ±20% |
| Holding torque | 0.55 Nm (5.5 kg-cm) |
| Detent torque | 20 mN·m |
| Leads | 4, 1000 mm cable, JST XHP-4 |
| Wire | UL1007 AWG24 |
| Insulation | Class B, 130 °C |
| Mass | 350 g |

Sources: `LDO-42STH48-2504AC-drawing.pdf` and the LDO product page.

### 5.7 MOONS' MS17HA (0.9°) and MS17HD (1.8°)

A broad industrial family with 4-lead bipolar and 6-lead unipolar
versions. The catalogue pages in the library include the electrical
tables, dimensions, and torque curves.

| Series | Step | Body (mm) | Current (A) | Torque (Nm) |
|---|---|---:|---:|---:|
| MS17HD5 | 1.8° | 25.3 | 0.27 to 1.5 | 0.20 to 0.21 |
| MS17HD4 | 1.8° | 34.3 | 0.4 to 1.5 | 0.32 to 0.34 |
| MS17HD2 | 1.8° | 39.8 | 0.4 to 2.0 | 0.48 to 0.50 |
| MS17HD6 | 1.8° | 48.3 | 0.5 to 2.0 | 0.62 to 0.67 |
| MS17HDB | 1.8° | 62.8 | 1.0 to 2.0 | 0.82 to 0.88 |
| MS17HA4 | 0.9° | 34.3 | 0.4 to 2.0 | 0.29 to 0.31 |
| MS17HA2 | 0.9° | 39.8 | 0.4 to 2.0 | 0.41 to 0.42 |
| MS17HA6 | 0.9° | 48.3 | 0.5 to 2.0 | 0.55 to 0.58 |

All models: 200 or 400 steps/rev, ±5% step accuracy, IP40, Class B,
UL Recognized file E465363, −20 °C to +50 °C. Axial load 25 N push and
65 N pull. Radial load 29 N at the flat centre.

Source: `Moons-MS17HA-MS17HD-series.pdf`, extracted from the MOONS'
catalogue pages 33 to 40.

### 5.8 Lin Engineering 4209 (0.9°)

A 0.9° motor with high step accuracy and a choice of series or parallel
windings.

| Model | Body (mm) | Connection | I (A) | R (Ω) | L (mH) | Torque (Nm) | Mass (lb) |
|---|---|---:|---:|---:|---:|---:|---:|
| 4209S-01S | 34 | Series | 0.67 | 9.6 | 18.4 | 0.22 | 0.44 |
| 4209S-01P | 34 | Parallel | 1.33 | 2.4 | 4.6 | 0.22 | 0.44 |
| 4209M-01S | 39.9 | Series | 0.84 | 6.1 | 15.2 | 0.36 | 0.56 |
| 4209M-01P | 39.9 | Parallel | 1.68 | 1.5 | 3.8 | 0.36 | 0.56 |
| 4209L-01S | 48 | Series | 0.84 | 7.6 | 21.2 | 0.44 | 0.70 |
| 4209L-01P | 48 | Parallel | 1.70 | 1.9 | 5.3 | 0.44 | 0.70 |

Source: `LinEngineering-4209-0.9deg.pdf`. The file also gives torque
curves and a 6-lead unipolar table.

### 5.9 Adafruit 324 / XY42STH34-0354A

A small 34 mm motor sold for Arduino motor shields.

| Item | Value |
|---|---|
| Step angle | 1.8° |
| Body length | 34 mm |
| Rated voltage | 12 V |
| Rated current | 0.35 A/phase |
| Phase resistance | 34 Ω |
| Phase inductance | 33 mH |
| Holding torque | 1.6 kg-cm (15.7 Ncm) |
| Detent torque | 120 g-cm |
| Rotor inertia | 35 g·cm² |
| Leads | 4 |
| Mass | 0.22 kg |
| Shaft | 5 mm D, 24 mm |

Source: `Adafruit-324-datasheet.pdf`.

The Adafruit product page lists 35 Ω, 28 oz-in, and a 42 mm body. The
manufacturer sheet lists 34 Ω, 1.6 kg-cm, and a 34 mm body. Use the
manufacturer sheet and measure your motor.

## 6. Wiring and connectors

### 6.1 Find the coil pairs

Wire colours are not standardized. Two batches of the same model can use
different colours. Do not connect a driver until you know the pairs.

1. Set a multimeter to resistance.
2. Probe pairs of leads.
3. A coil pair reads a low resistance, usually 1 Ω to 35 Ω.
4. Leads from different coils read open circuit.
5. On a 6-lead motor, the centre tap reads about half the coil resistance
   to each end.

### 6.2 Common colour codes

| Motor | Coil A | Coil B | Notes |
|---|---|---|---|
| 17HS4401, 17HS4401S, 17HS19-2004S1 | Black A+, Green A− | Red B+, Blue B− | Common StepperOnline order |
| Older 17HS4401 batches | Red A+, Green A− | Yellow B+, Blue B− | Check with a meter |
| Pololu #2267 | Black, Green | Red, Blue | 4 leads |
| Pololu #1200 | Black, Green (Yellow tap) | Red, Blue (White tap) | 6 leads |
| Trinamic QSH4218 | Black A, Green A− | Red B, Blue B− | 4 leads |
| LDO-42STH48-2504AC | Black A, Green C | Red B, Blue D | JST XHP-4 |
| Adafruit 324 | Red, Yellow | Green, Brown/Gray | 4 leads |

If the motor turns the wrong way, swap one coil pair. Do not swap a
single lead inside a pair.

### 6.3 Connectors

- 4-pin JST-XH or JST-PH 2.54 mm: common on 3D-printer motors.
- 4-pin Molex / Harwin 2.54 mm: StepperOnline and Duet boards.
- 6-pin JST-PH: MOONS' 4-lead and 6-lead motors use a 6-pin housing with
  some positions unused. Check the pin table in the drawing.
- Bare tinned leads: Pololu, Lin, and some 17HS motors.

## 7. Driver setup

### 7.1 Current

Most datasheets in this library rate current per phase for full-step,
two-phase-on operation. A chopper driver with an RMS current setting
needs a lower value.

```
I_RMS ≈ I_rated / √2 ≈ 0.707 × I_rated
```

Example: 17HS4401 is rated 1.7 A per phase.

```
I_RMS = 1.7 × 0.707 = 1.20 A
```

Set the run current to 1.2 A RMS. Set the hold current to 0.5 to 0.7 of
the run current if the driver supports it.

Some drivers label the setting as peak current. In that case use the
rated value directly. Read the driver manual. Do not guess.

### 7.2 Supply voltage

A stepper datasheet "rated voltage" is not the supply voltage. It is the
DC voltage across one phase at rated current.

Use the Trinamic rule from `Trinamic-QSH4218-manual.pdf` section 6.3:

```
U_coil_nom = I_rated × R_phase
U_supply   = 4 × U_coil_nom to 22 × U_coil_nom
U_max      = 25 × U_coil_nom
```

Example: 17HS4401, 1.7 A and 1.5 Ω.

```
U_coil_nom = 1.7 × 1.5 = 2.55 V
U_supply   = 10.2 V to 56 V
```

A 24 V supply is a good default. A 12 V supply works but the torque falls
at higher speed.

### 7.3 Microstepping

| Microstep | Steps/rev, 1.8° | Steps/rev, 0.9° |
|---:|---:|---:|
| 1 | 200 | 400 |
| 2 | 400 | 800 |
| 4 | 800 | 1600 |
| 8 | 1600 | 3200 |
| 16 | 3200 | 6400 |
| 32 | 6400 | 12800 |
| 64 | 12800 | 25600 |
| 128 | 25600 | 51200 |
| 256 | 51200 | 102400 |

Microstepping improves smoothness and resolution. It does not increase
holding torque. Torque falls as the microstep count rises.

### 7.4 Heat

All motors in this library use Class B insulation, rated 130 °C. The
datasheets allow an 80 °C temperature rise at rated current with two
phases on. A motor case at 60 °C to 80 °C is normal. A case above 90 °C
is a warning sign.

Reduce the current or the duty cycle if the motor is too hot. A heatsink
or a fan helps. Do not exceed the insulation class.

## 8. Selection guide

| Need | Suggested model | Why |
|---|---|---|
| General 3D-printer X/Y, 24 V | 17HS4401 or 17HS19-2004S1 | Common, cheap, good torque |
| Light extruder | 17HS08-1004S or LDO-42STH25-0404 | Short and light |
| High torque in 48 mm | LDO-42STH48-2504AC or 17HS19-2004S1 | 55 to 59 Ncm |
| Quiet, smooth motion | QSH4218-51-10-049 | 1 A winding, published curves |
| High speed | QSH4218-47-28-040 | 0.6 mH, 2.8 A |
| 0.9° resolution | Lin 4209M-01P or MS17HA2P4100 | 400 steps/rev |
| 6-lead unipolar or bipolar | SY42STH47-1206A | Centre taps |
| 60 mm high torque | 17HS6403 or MS17HDBP4100 | 80 to 82 Ncm |
| 12 V Arduino shield | Adafruit 324 | 0.35 A, 34 Ω |

## 9. Document index

| File | Pages | Publisher | Best for |
|---|---:|---|---|
| `Leison-17HS-series.pdf` | 1 | Ningbo Leison | Full 17HS table, 20 mm to 63 mm |
| `MotionKing-17HS-series-catalog.pdf` | 1 | MotionKing | Cross-check of the 17HS table |
| `Handson-17HS4401S.pdf` | 3 | Handson Technology | 17HS4401S, dimensions, body-length chart |
| `StepperOnline-17HS19-2004S1.pdf` | 1 | StepperOnline | 48 mm, 2 A, 59 Ncm |
| `StepperOnline-17HS19-2004S1-torque-curve.pdf` | 1 | StepperOnline | Speed-torque curve |
| `StepperOnline-17HS08-1004S-pancake.pdf` | 1 | StepperOnline | 20 mm pancake |
| `Pololu-2267-SY42STH38-1684A.pdf` | 2 | SOYO / Pololu | 38 mm, 1.68 A |
| `Pololu-1200-SY42STH47-1206A.pdf` | 1 | SOYO / Pololu | 48 mm, 6-lead |
| `Trinamic-QSH4218-manual.pdf` | 13 | Trinamic / ADI | 4 models, torque curves, driver theory |
| `LDO-42STH-series-info-sheet.pdf` | 1 | LDO Motors | Wide winding table |
| `LDO-42STH48-2504AC-drawing.pdf` | 1 | LDO Motors | 2.5 A, 0.55 Nm drawing |
| `Moons-MS17HA-MS17HD-series.pdf` | 8 | MOONS' | 0.9° and 1.8°, 25 mm to 63 mm |
| `LinEngineering-4209-0.9deg.pdf` | 2 | Lin Engineering | 0.9°, series/parallel windings |
| `Adafruit-324-datasheet.pdf` | 1 | Adafruit / XY | 34 mm, 0.35 A |
| `NEMA-ICS16-2001-flange-17-excerpt.pdf` | 2 | NEMA | Official flange 17 table |

## 10. Sources and checks

Each PDF is the publisher file, except where noted below. The source URL,
publisher, page count, and SHA-256 are in
[`datasheets/SOURCES.md`](datasheets/SOURCES.md).

Changes made during collection:

- `Moons-MS17HA-MS17HD-series.pdf` is an 8-page extract of the MOONS'
  catalogue (pages 33 to 40).
- `NEMA-ICS16-2001-flange-17-excerpt.pdf` is a 2-page extract of
  NEMA ICS 16-2001 (pages 59 and 60).
- `Adafruit-324-datasheet.pdf` is the Adafruit JPG converted to PDF. The
  image is unchanged.

Check the files:

```sh
cd datasheets
sha256sum -c SHA256SUMS.txt
```

## 11. Limits

- The library has no motor that this project measured. Every value is a
  manufacturer claim.
- Some vendors publish different values on the product page and in the
  PDF. The PDF values are used here. The differences are noted.
- A datasheet can be out of date. Measure the resistance and body length
  of your motor before you set the driver current.
- This document is a reference, not a wiring instruction for a specific
  board. Check the pinout of your driver board.
