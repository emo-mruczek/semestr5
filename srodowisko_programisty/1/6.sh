#!/usr/bin/env bash

files=$(find "$1" -type f)

for file in $files
do
    awk ' {
        split($0, words, /[^a-zA-Z0-9]+/);
        for ( i in words ) {
            word = words[i];
            if ( word != "" ) count[word]++;
        }

        for ( word in count ) {
            if ( count[word] > 1 ) {
                print "FILE: ", FILENAME;
                print "LINE: ", $0;
                print "WORD: ", word;
            }
        }
    }' "${file}"
done


