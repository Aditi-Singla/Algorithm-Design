#!/bin/bash

if [ -f evenpath.class ]; then
    if [ "$#" == 2 ]; then
        java evenpath "$1" "$2"
    else
        echo "Illegal number of parameters ($#)"
    fi
else
    echo "Executable not found, run compile.sh first"
fi