#!/bin/bash

if [ -f eggdrop ]; then
    if [ "$#" == 2 ]; then
    	./eggdrop "$1" "$2"
    else
        echo "Illegal number of parameters ($#)"
    fi
else
    echo "Executable not found, run compile.sh first"
fi