#!/usr/bin/env bash

rev=$1
url=$2
tempd=$(mktemp -d)
svn checkout -r "$rev" "$url" "$tempd" >/dev/null 2>&1

words=$(find "$tempd" -type f -exec cat {} + | grep --exclude-dir=".svn" -o '\w*' | sort | uniq)
for word in $words
do
    count=$(grep --exclude-dir=".svn" -l -R -w "$word" "$tempd" | wc -l)
    echo "$count $word"
done | sort -r | uniq

rm -rf "$tempd"
