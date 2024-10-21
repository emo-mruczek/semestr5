#!/usr/bin/env bash

input_directory="4"
output_file="res.txt"
program="./main"


if [ ! -f "$output_file" ]; then
  touch "$output_file"
fi

for file in "$input_directory"/*; do
  if [ -f "$file" ]; then
    echo "Processing $file..."
    echo "File: $file" >> "$output_file"
    cat "$file" | $program >> "$output_file"
  else
    echo "Skipping $file, not a regular file."
  fi
done

