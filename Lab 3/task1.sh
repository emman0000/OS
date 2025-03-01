#!/bin/bash

#If the two numbers are exactly the same

if [ "$#" -ne 2 ]; then
   echo "Usage: $0 num1 num2"
   exit 1
fi

result=$(($1*$2))

echo "The product of the two numbers $1 and $2 is: $result"
