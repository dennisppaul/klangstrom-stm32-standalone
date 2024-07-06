#!/bin/zsh

format_files() {
    local DIR="$1"
    local CONFIG_FILE="$2"

    # Check if the directory exists
    if [ ! -d "$DIR" ]; then
        echo "Error: Directory $DIR does not exist."
        exit 1
    fi

    # Check if the configuration file exists
    if [ ! -f "$CONFIG_FILE" ]; then
        echo "Error: Configuration file $CONFIG_FILE does not exist."
        exit 1
    fi

    find "$DIR" -type f \( -name '*.c' -o -name '*.cpp' -o -name '*.h' -o -name '*.hpp' \) | while read -r FILE; do
        echo "Formatting $FILE"
        clang-format -i -style=file -assume-filename="$CONFIG_FILE" "$FILE"
    done
}

# Check if the correct number of arguments is provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <directory> <clang-format-config>"
    exit 1
fi

# Directory to format and the clang-format config file
TARGET_DIR="$1"
CLANG_FORMAT_CONFIG="$2"

# Call the function
format_files "$TARGET_DIR" "$CLANG_FORMAT_CONFIG"