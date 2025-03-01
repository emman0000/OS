#!/bin/bash

#one argument check 
if [ "$#" -ne 1 ]; then
   echo "Usage: $0 filename"
   exit 1
fi
#Storing name 
filename="$1"

if [ -e "$filename" ]; then
   echo "$(date)" >> "$filename"
   echo "Date and time appended to $filename"
else 
   echo "File '$filename' does not exits"
fi
