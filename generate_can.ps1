
$DBC_FILE = "QUTMS.dbc"
$INC_DIR = "Inc"
$SRC_DIR = "Src"
$DATABASE_NAME = "qutms"
$TEMP_DIR = "temp_can_gen"

# --- Script Logic ---

# Check if DBC file exists
if (-not (Test-Path $DBC_FILE)) {
    Write-Host "Error: DBC file not found at '$DBC_FILE'" -ForegroundColor Red
    exit 1
}

# Create a temporary directory for the generated files
Write-Host "Creating temporary directory: $TEMP_DIR"
New-Item -ItemType Directory -Force -Path $TEMP_DIR | Out-Null

# Generate the C code using cantools
Write-Host "Generating C code from $DBC_FILE..."
try {
    # Try running via python module which is safer than relying on PATH scripts
    python -m cantools generate_c_source --database-name "$DATABASE_NAME" --output-directory "$TEMP_DIR" "$DBC_FILE"
    if ($LASTEXITCODE -ne 0) { throw "cantools failed" }
}
catch {
    Write-Host "Error: Code generation failed. Check for errors in your DBC file or ensure cantools is installed (pip install cantools)." -ForegroundColor Red
    Remove-Item -Recurse -Force $TEMP_DIR
    exit 1
}

# Check if code generation was successful
if (-not (Test-Path "$TEMP_DIR\$DATABASE_NAME.c")) {
    Write-Host "Error: Code generation failed. Output file not found." -ForegroundColor Red
    Remove-Item -Recurse -Force $TEMP_DIR
    exit 1
}

# Ensure the destination directories exist
Write-Host "Creating destination directories if they don't exist..."
New-Item -ItemType Directory -Force -Path $INC_DIR | Out-Null
New-Item -ItemType Directory -Force -Path $SRC_DIR | Out-Null

# Move the generated header file to the Inc folder
Write-Host "Moving $DATABASE_NAME.h to $INC_DIR\"
Move-Item -Force "$TEMP_DIR\$DATABASE_NAME.h" "$INC_DIR\"

# Move the generated source file to the Src folder
Write-Host "Moving $DATABASE_NAME.c to $SRC_DIR\"
Move-Item -Force "$TEMP_DIR\$DATABASE_NAME.c" "$SRC_DIR\"

# Remove the temporary directory
Write-Host "Cleaning up temporary directory..."
Remove-Item -Recurse -Force $TEMP_DIR

Write-Host "CAN code has been generated and placed in:" -ForegroundColor Green
Write-Host "Header: $INC_DIR\$DATABASE_NAME.h"
Write-Host "Source: $SRC_DIR\$DATABASE_NAME.c"
