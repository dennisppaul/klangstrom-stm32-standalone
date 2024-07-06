#! /bin/zsh

# this script compiles all file from the file list into a folder

KLST_CUBEMX_LIB_PATH=../libraries/klangstrom-libraries/Klangstrom_KLST_PANDA_STM32_CubeMX
KLST_STM32_LIB_PATH=../libraries/klangstrom-stm32

./collect_files.sh \
    $KLST_CUBEMX_LIB_PATH/filelist.txt \
    $KLST_STM32_LIB_PATH \
    $KLST_CUBEMX_LIB_PATH/src

# should be formated already
# ./clang-format-folder.sh \
#     $KLST_CUBEMX_LIB_PATH/src \
#     $KLST_CUBEMX_LIB_PATH/.clang-format
