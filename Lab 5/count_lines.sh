#!/bin/bash

# Prompt user for filename
echo -n "Enter the filename: "
read filename

# Check if file exists
if [ -f "$filename" ]; then
    # Count and display number of lines
    line_count=$(wc -l < "$filename")
    echo "The file '$filename' has $line_count lines."
else
    echo "Error: File '$filename' not found."
fi

