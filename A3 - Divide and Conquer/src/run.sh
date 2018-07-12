#!/bin/bash

if [ -f karatsuba ] && [ -f longmultiplication ]; then
    if [ "$#" == 3 ]; then
    	if [ "$1" == "-karatsuba" ]; then
        	./karatsuba "$2" "$3"
        elif [ "$1" == "-longmultiplication" ]; then
        	./longmultiplication "$2" "$3"
        else
        	echo "Illegal method type"
        fi
    else
        echo "Illegal number of parameters ($#)"
    fi
else
    echo "Executable not found, run compile.sh first"
fi