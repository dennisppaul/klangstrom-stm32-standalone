#!/bin/zsh

source stm32duino.config
VARIANT_PATH=../variants/KLST_PANDA

echo "removing all symlinks from '$ARDUINO_STM32DUINO_PATH'"
./remove_linked_variant_files.sh "$ARDUINO_STM32DUINO_PATH"
./link_variant_files.sh $VARIANT_PATH/variant "$ARDUINO_STM32DUINO_PATH"
