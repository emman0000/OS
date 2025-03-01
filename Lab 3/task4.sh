#!/bin/bash

# Check if the user provided an argument (filename or directory name)
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <file_or_directory>"
    exit 1
fi

# Store the input argument
item="$1"

# Check if it exists
if [ ! -e "$item" ]; then
    echo "Error: '$item' does not exist."
    exit 1
fi

# Check if it is a file or directory
if [ -f "$item" ]; then
    echo "'$item' is a file."
    echo "File size: $(stat -c%s "$item") bytes"
    echo "Permissions: $(ls -l "$item" | awk '{print $1}')"
    echo "Last modified: $(stat -c%y "$item")"
elif [ -d "$item" ]; then
    echo "'$item' is a directory."
    echo "Number of files: $(ls -1 "$item" | wc -l)"
    echo "Permissions: $(ls -ld "$item" | awk '{print $1}')"
    echo "Last modified: $(stat -c%y "$item")"
else
    echo "'$item' is neither a regular file nor a directory."
fi

