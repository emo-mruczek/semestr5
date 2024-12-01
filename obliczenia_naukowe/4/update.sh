#!/usr/bin/env bash

name=sprawozdanie.tex

inotifywait -q -m -e close_write $name |
while read -r; do
    pdflatex $name
done
