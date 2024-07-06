# klangstrom-stm32-standalone / tools

## Klangstrom_KLST_PANDA_STM32_CubeMX

@updated(2024-07-06)

after code has been generated with STM32CubeMX in `‌./libraries/klangstrom-stm32` the following scripts should be run:

1. `‌klangstrom-stm32-format-generated.sh` :: format generated code
2. `‌KLST_PANDA_STM32_CubeMX-compile_filelist.sh` :: compiles a list of generated files from `‌klangstrom-stm32`
3. `‌KLST_PANDA_STM32_CubeMX-collect_files.sh` :: collect and copy files spec'd in the file list to `./libraries/klangstrom-libraries/Klangstrom_KLST_PANDA_STM32_CubeMX`

`KLST_PANDA-directories.txt` contains a list of directories to be considered for `./libraries/klangstrom-libraries/Klangstrom_KLST_PANDA_STM32_CubeMX`

currently these are:

- `./libraries/klangstrom-stm32/Core/Inc`
- `./libraries/klangstrom-stm32/Core/Src` ( except `‌system_stm32h7xx.c` )
- `./libraries/klangstrom-stm32/FATFS/App`
- `./libraries/klangstrom-stm32/FATFS/Target`
- `./libraries/klangstrom-stm32/Middlewares/Third_Party/FatFs/src`

## Variant

the following scripts are for development purposes only. they try to establish a development workflow for *Arduino IDE* i.e symlinking libraries and hardware definitions into 

- `KLST_PANDA-update_variant.sh` :: symlinks all files in the local `variant` folder into the *STM32duino* variant folder.
- `‌link_libraries.sh` :: creates symlink for libraries specified in 
- `‌./variants/KLST_PANDA/KLST_PANDA-boards.txt` :: may need to be appended to variant board definition

currently the following files are relevant for a variant:

```
PeripheralPins_KLST_PANDA.c
STM32H723ZGTX_FLASH.ld
variant_KLST_PANDA.cpp
variant_KLST_PANDA.h
```

note, that the source files rely on `ARDUINO_KLST_PANDA` being defined. `STM32H723ZGTX_FLASH.ld` may be copied from `‌./libraries/klangstrom-stm32`. 
