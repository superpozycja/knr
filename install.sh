#!/bin/sh

mkdir bin

for dir in c*/; do
    if [ -d "$dir" ]; then
        cd "$dir"
        for file in ./*.c; do
            echo $file
            echo $(basename -s .c $file)
            cc -g -o "../bin/$(echo $dir | head -c 2)_$(basename -s .c $file)" $file -lm
        done
	cd ..
    fi
done
