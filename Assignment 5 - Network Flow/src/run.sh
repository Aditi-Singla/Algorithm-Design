#!/bin/bash

if [ -f tile ]; then
    if [ "$#" == 2 ]; then
    	./tile "$1" "$2"
    else
        echo "Illegal number of parameters ($#)"
    fi
else
    echo "Executable not found, run compile.sh first"
fi