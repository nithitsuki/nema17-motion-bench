# Board sources

This page lists the source files for the WeAct Studio STM32G474CEU6 core
board. The "Long" board uses the QFN48 package. The "short" board uses
QFP48 and the STM32G474CBT6. Do not mix the two schematics.

## WeAct Studio (board vendor)

Repository: <https://github.com/WeActStudio/WeActStudio.STM32G474CoreBoard>

| Document | Link |
|---|---|
| Long board schematic, V1.0, QFN48 | <https://github.com/WeActStudio/WeActStudio.STM32G474CoreBoard/raw/master/Hardware/QFN48/WeAct-STM32G474CoreBoard_Long/WeAct-STM32G474CoreBoard_Long_V10%20SchDoc.pdf> |
| Long board shape and dimensions | <https://github.com/WeActStudio/WeActStudio.STM32G474CoreBoard/raw/master/Hardware/QFN48/WeAct-STM32G474CoreBoard_Long/WeAct-STM32G474CoreBoard_Long_V10%20Board%20Shape%20%E5%A4%96%E5%BD%A2.pdf> |
| Long board 3D model (STEP) | <https://github.com/WeActStudio/WeActStudio.STM32G474CoreBoard/raw/master/Hardware/QFN48/WeAct-STM32G474CoreBoard_Long/WeAct-STM32G474CoreBoard_Long_V10%203D.step> |
| Short board schematic, V1.0, QFP48 | <https://github.com/WeActStudio/WeActStudio.STM32G474CoreBoard/raw/master/Hardware/QFP48/WeAct-STM32G47xCxTxCoreBoard_V10_SchDoc.pdf> |
| Board photos | <https://github.com/WeActStudio/WeActStudio.STM32G474CoreBoard/tree/master/Images> |
| Vendor examples (CubeMX, MDK-ARM) | <https://github.com/WeActStudio/WeActStudio.STM32G474CoreBoard/tree/master/Examples> |
| Vendor download tool | <https://github.com/WeActStudio/WeActStudio.STM32G474CoreBoard/tree/master/Tools> |

The repository also mirrors these files in its `Doc` folder:

- `STM32G474xE_DS12288.pdf` (datasheet)
- `STM32G4_Referencemanual_RM0440.pdf` (reference manual)
- `an2606-stm32-microcontroller-system-memory-boot-mode-stmicroelectronics.pdf`
- `an5225-usb-typec-power-delivery-using-stm32-mcus-and-mpus-stmicroelectronics.pdf`
- `ME6239_VIN=30V,VOUT=3.3V 250MA.PDF` (regulator)

Mirror index: <https://github.com/WeActStudio/WeActStudio.STM32G474CoreBoard/tree/master/Doc>

## STMicroelectronics

| Document | Link |
|---|---|
| STM32G474CE product page | <https://www.st.com/en/microcontrollers-microprocessors/stm32g474ce.html> |
| Datasheet DS12288, STM32G474xE | <https://www.st.com/resource/en/datasheet/stm32g474ce.pdf> |
| Reference manual RM0440, STM32G4 series | <https://www.st.com/resource/en/reference_manual/rm0440-stm32g4-series-advanced-armbased-32bit-mcus-stmicroelectronics.pdf> |
| Programming manual PM0223, Cortex-M4 | <https://www.st.com/resource/en/programming_manual/pm0223-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf> |
| Application note AN2606, system memory boot mode | <https://www.st.com/resource/en/application_note/an2606-stm32-microcontroller-system-memory-boot-mode-stmicroelectronics.pdf> |
| Errata sheet ES0430, STM32G474xx | <https://www.st.com/resource/en/errata_sheet/es0430-stm32g474xx-device-errata-stmicroelectronics.pdf> |
| Application note AN5225, USB Type-C Power Delivery | <https://www.st.com/resource/en/application_note/an5225-usb-typec-power-delivery-using-stm32-mcus-and-mpus-stmicroelectronics.pdf> |
| STM32CubeProgrammer | <https://www.st.com/en/development-tools/stm32cubeprog.html> |
| STM32CubeIDE | <https://www.st.com/en/development-tools/stm32cubeide.html> |
| STM32CubeMX | <https://www.st.com/en/development-tools/stm32cubemx.html> |

ST.com blocks some networks and automated clients. If a link times out,
use the mirror in the WeAct `Doc` folder.

## PlatformIO and Arduino core

| Item | Link |
|---|---|
| Board definition `weact_g474ceu6` | <https://github.com/platformio/platform-ststm32/blob/develop/boards/weact_g474ceu6.json> |
| STM32duino variant header | <https://github.com/stm32duino/Arduino_Core_STM32/blob/main/variants/STM32G4xx/G473C(B-C-E)U_G474C(B-C-E)U_G483CEU_G484CEU/variant_WEACT_G474CE.h> |
| STM32duino variant source | <https://github.com/stm32duino/Arduino_Core_STM32/blob/main/variants/STM32G4xx/G473C(B-C-E)U_G474C(B-C-E)U_G483CEU_G484CEU/variant_WEACT_G474CE.cpp> |
| STM32duino peripheral map | <https://github.com/stm32duino/Arduino_Core_STM32/blob/main/variants/STM32G4xx/G473C(B-C-E)U_G474C(B-C-E)U_G483CEU_G484CEU/PeripheralPins.c> |
| PlatformIO ST STM32 platform | <https://github.com/platformio/platform-ststm32> |

## Check the board revision

Read the revision text on the PCB silkscreen. This pinout applies to
revision V1.0. Check the vendor repository before you rely on it for a
different revision.
