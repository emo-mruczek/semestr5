#!/usr/bin/env bash

files=$(find "$1" -type f)
declare -A dict

for file in $files
do 
    for word in $(cat "$file")
    do
        if [ "${dict[$word]}" == "" ]; then
            dict[$word]=0
        else
            dict[$word]=$(( ${dict[$word]} + 1))
        fi
    done
done
