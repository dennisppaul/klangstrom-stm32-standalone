#! /bin/zsh

# this script generates a list of files to be collected into a single library folder ( e.g `Klangstrom_KLST_PANDA_STM32_CubeMX` )

SCRIPT_PATH=$(realpath "$0")
SCRIPT_DIR=$(dirname "$SCRIPT_PATH")

CUBEMX_GENERATED_PROJECT_PATH=../libraries/klangstrom-stm32
KLST_LIBRARY_PATH=../libraries/klangstrom-libraries/Klangstrom_KLST_PANDA_STM32_CubeMX
OUTPUT_FILENAME=$SCRIPT_DIR/$KLST_LIBRARY_PATH/filelist.txt
DIRECTORIES_FILE=$SCRIPT_DIR/KLST_PANDA-directories.txt

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
rm -f "$OUTPUT_FILENAME"

# Check if the directories file exists
if [ ! -f "$DIRECTORIES_FILE" ]; then
    echo "Error: Directories file $DIRECTORIES_FILE does not exist."
    exit 1
fi

# Read directories from the file and call the function for each
while IFS= read -r REL_DIR; do
    if [ -n "$REL_DIR" ]; then
        find_files "$SCRIPT_DIR/$CUBEMX_GENERATED_PROJECT_PATH" "$REL_DIR" "$OUTPUT_FILENAME"
    fi
done < "$DIRECTORIES_FILE"

echo "File list '$OUTPUT_FILENAME' is saved to: $(realpath $OUTPUT_FILENAME)"

# echo "Note, that not all files should go into this list. Remove the unwanted files manually (e.g., 'Core/Src/system_stm32h7xx.c' and 'Core/Startup/startup_stm32h723zgtx.s')."
# echo "Note, that there is a problem with file '../libraries/klangstrom-stm32/Middlewares/Third_Party/FatFs/src/option/syscall.c' which overwrites '../libraries/klangstrom-stm32/Core/Src/syscalls.c'"