#! /bin/zsh

# this script generates a list of files that are collected into a single library folder ( e.g `Klangstrom_KLST_PANDA_STM32_CubeMX` )

SCRIPT_PATH=$(realpath "$0")
SCRIPT_DIR=$(dirname "$SCRIPT_PATH")

CUBEMX_GENERATED_PROJECT_PATH=../libraries/klangstrom-stm32
KLST_LIBRARY_PATH=../libraries/klangstrom-libraries/Klangstrom_KLST_PANDA_STM32_CubeMX
OUTPUT_FILENAME=$SCRIPT_DIR/$KLST_LIBRARY_PATH/filelist.txt

find_files() {
    local BASE_DIR="$1"
    local REL_DIR="$2"
    local OUTPUT_FILE="$3"

    find "$BASE_DIR/$REL_DIR" -type f \
        -not -name '.DS_Store' \
        -not -name '*.s' \
        -not -name 'system_stm32h7xx.c' \
        | sed "s|^$BASE_DIR/||" \
        | sort >> "$OUTPUT_FILE"
}

# Ensure the output directory exists
mkdir -p "$(dirname "$OUTPUT_FILENAME")"

# Clear the output file if it exists
rm "$OUTPUT_FILENAME"

# Call the function for each directory
find_files "$SCRIPT_DIR/$CUBEMX_GENERATED_PROJECT_PATH" "Core" "$OUTPUT_FILENAME"
find_files "$SCRIPT_DIR/$CUBEMX_GENERATED_PROJECT_PATH" "FATFS" "$OUTPUT_FILENAME"
find_files "$SCRIPT_DIR/$CUBEMX_GENERATED_PROJECT_PATH" "Middlewares/Third_Party/FatFs" "$OUTPUT_FILENAME"

echo "file list '$OUTPUT_FILENAME' is saved to: $(realpath $OUTPUT_FILENAME)"
echo
echo "note, that not all files should go into this list. remove the unwanted files manually ( e.g 'Core/Src/system_stm32h7xx.c' and 'Core/Startup/startup_stm32h723zgtx.s')."
echo "note, that there is a problem with file '../libraries/klangstrom-stm32/Middlewares/Third_Party/FatFs/src/option/syscall.c' which overwrites '../libraries/klangstrom-stm32/Core/Src/syscalls.c'" 
