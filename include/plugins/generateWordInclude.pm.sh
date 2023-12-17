#!/bin/bash

# Input file containing words
input_file="words.txt"

# Output C++ header file
output_file="WordList.h"

# Check if the input file exists
if [ ! -f "$input_file" ]; then
    echo "Input file '$input_file' not found."
    exit 1
fi

# Create the header file and write the header guards and namespace
echo "#pragma once" > "$output_file"
echo "#include <pgmspace.h>" >> "$output_file"
echo "#include <string>" >> "$output_file"
echo "" >> "$output_file"
echo "namespace WordConstants {" >> "$output_file"
echo "    const char* const wordList[] PROGMEM = {" >> "$output_file"

# Read each word from the input file and write it as a constant in the header file
index=0
while IFS= read -r word || [[ -n "$word" ]]; do
    echo "        \"$word\"," >> "$output_file"
    ((index++))
done < "$input_file"

# Finish the namespace and close the header file
echo "    };" >> "$output_file"
echo "}" >> "$output_file"

echo "WordList.h generated successfully."
