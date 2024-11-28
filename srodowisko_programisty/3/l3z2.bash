#!/usr/bin/env bash

rev=$1
url=$2
tempd=$(mktemp -d)
svn checkout -r "$rev" "$url" "$tempd" >/dev/null 2>&1
find "$tempd" -type f -exec cat {} + | grep --exclude-dir=".svn" -o '\w*' | sort | uniq -c | sort -nr

rm -rf "$tempd"
