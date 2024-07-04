# klangstrom-stm32-standalone / tools

@note(`klangstrom-stm32` currently only works for `KLST_PANDA`) 

## Klangstrom_KLST_PANDA_STM32_CubeMX

copy generated files from `./libraries/klangstrom-stm32/` 

- `./libraries/klangstrom-stm32/Core/Inc`
- `./libraries/klangstrom-stm32/Core/Src` ( except `‌system_stm32h7xx.c` )
- `./libraries/klangstrom-stm32/FATFS/App`
- `./libraries/klangstrom-stm32/FATFS/Target`
- `./libraries/klangstrom-stm32/Middlewares/Third_Party/FatFs/src`
- `./libraries/klangstrom-stm32/STM32H723ZGTX_FLASH.ld`
- `‌./libraries/klangstrom-libraries/Klangstrom/src/KlangstromEnvironment.h`

to `./libraries/klangstrom-libraries/Klangstrom_KLST_PANDA_STM32_CubeMX/src`

## variant

add the following files to `variant` folder:

```
PeripheralPins_KLST_PANDA.c
STM32H723ZGTX_FLASH.ld
variant_KLST_PANDA.cpp
variant_KLST_PANDA.h
```

copy file `./libraries/klangstrom-stm32/STM32H723ZGTX_FLASH.ld` to `variant` folder.

copy file `‌KlangstromEnvironment.h` to `variant` folder.

append `./variants/KLST_PANDA/KLST_PANDA-boards.txt` to `board.txt` file in `$HOME/Library/Arduino15/packages/STMicroelectronics/hardware/stm32/2.8.0/boards.txt`