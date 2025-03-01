#!/bin/bash

# Check if the user provided input
if [ "$#" -eq 0 ]; then
    echo "Usage: $0 \"your sentence here\""
    exit 1
fi

# Combine all arguments into a single sentence
sentence="$*"

# Convert sentence to lowercase and count vowels
vowel_count=$(echo "$sentence" | tr '[:upper:]' '[:lower:]' | grep -o '[aeiou]' | wc -l)

# Print the result
echo "The number of vowels in the sentence is: $vowel_count"

