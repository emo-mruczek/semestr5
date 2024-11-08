#!/usr/bin/env bash

name=zad_5_lista_2.tex

inotifywait -q -m -e close_write $name |
while read -r; do
    pdflatex $name
done
