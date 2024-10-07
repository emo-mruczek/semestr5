#!/usr/bin/env bash

words=$(find "$1" -type f -exec cat {} + | grep -v '^[ ]*$' | sort | uniq)

for word in $words
do
    echo "WORD $word: "
    files=$(find "$1" -type f)
    for file in $files
    do
        matches=$(grep -w "${word}" "$file" 2>/dev/null)
        if [ -n "$matches" ] 
        then
            echo "FILE: $file: "
            echo "LINE: $matches"
        fi
    done
done


