#!/bin/zsh

VARIANT_PATH=../variants/KLST_CATERPILLAR

# ./collect_variant_files.sh $VARIANT_PATH/KLST_PANDA-variant-files.txt ../libraries/klangstrom-stm32 $VARIANT_PATH/variant
./link_variant_files.sh $VARIANT_PATH/variant $HOME/Library/Arduino15/packages/STMicroelectronics/hardware/stm32/2.7.1/variants/STM32H7xx/H723Z\(E-G\)T_H730ZBT_H733ZGT
# ./link_libraries.sh ../KLST_PANDA/firmware/KLST_PANDA-libraries.txt ../KLST_PANDA/firmware $HOME/Documents/Arduino/libraries
