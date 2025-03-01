#!/bin/bash

# Check if the user provided a directory path
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <directory_path>"
    exit 1
fi

# Store the input directory
source_dir="$1"

# Check if the source directory exists
if [ ! -d "$source_dir" ]; then
    echo "Error: Directory '$source_dir' does not exist."
    exit 1
fi

# Define backup directory with a timestamp
backup_dir="backup_$(basename "$source_dir")_$(date +%Y%m%d_%H%M%S)"

# Create the backup directory
mkdir -p "$backup_dir"

# Copy files and directories to the backup directory
cp -r "$source_dir"/* "$backup_dir"

# Count the number of files and directories backed up
file_count=$(find "$backup_dir" -type f | wc -l)
dir_count=$(find "$backup_dir" -type d | wc -l)

# Display backup summary
echo "Backup completed successfully!"
echo "Backup folder: $backup_dir"
echo "Total files backed up: $file_count"
echo "Total directories backed up: $((dir_count - 1))" # Exclude the backup folder itself

