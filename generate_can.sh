#!/bin/bash

# --- Configuration ---
# Path to your DBC file
DBC_FILE="QUTMS.dbc"

# Desired output directories
INC_DIR="Inc"
SRC_DIR="Src"

# The base name for the generated files (e.g., qutms_can.c, qutms_can.h)
# This will also be the prefix for all generated functions.
DATABASE_NAME="qutms"

# Temporary directory for code generation
TEMP_DIR="temp_can_gen"

# --- Script Logic ---

# Check if DBC file exists
if [ ! -f "$DBC_FILE" ]; then
    echo "Error: DBC file not found at '$DBC_FILE'"
    exit 1
fi

# Create a temporary directory for the generated files
echo "Creating temporary directory: $TEMP_DIR"
mkdir -p "$TEMP_DIR"

# Generate the C code using cantools
echo "Generating C code from $DBC_FILE..."
cantools generate_c_source --database-name "$DATABASE_NAME" --output-directory "$TEMP_DIR" "$DBC_FILE"


# Check if code generation was successful
if [ ! -f "$TEMP_DIR/$DATABASE_NAME.c" ]; then
    echo "Error: Code generation failed. Check for errors in your DBC file."
    rm -rf "$TEMP_DIR"
    exit 1
fi

# Ensure the destination directories exist
echo "Creating destination directories if they don't exist..."
mkdir -p "$INC_DIR"
mkdir -p "$SRC_DIR"

# Move the generated header file to the Inc folder
echo "Moving $DATABASE_NAME.h to $INC_DIR/"
mv "$TEMP_DIR/$DATABASE_NAME.h" "$INC_DIR/"

# Move the generated source file to the Src folder
echo "Moving $DATABASE_NAME.c to $SRC_DIR/"
mv "$TEMP_DIR/$DATABASE_NAME.c" "$SRC_DIR/"

# Remove the temporary directory
echo "Cleaning up temporary directory..."
rm -rf "$TEMP_DIR"

echo "CAN code has been generated and placed in:"
echo "Header: $INC_DIR/$DATABASE_NAME.h"
echo "Source: $SRC_DIR/$DATABASE_NAME.c"
