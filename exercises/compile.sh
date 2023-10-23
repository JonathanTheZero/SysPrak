#!/bin/bash

if [ -z "$1" ]; then
    echo "You didn't enter any arguments."
    exit 1
fi

if [ ! -f "$1/main.c" ]; then
    echo "No main.c file found in the specified directory."
    exit 1
fi

# Create dist if it does not exist
if [ ! -d "dist" ]; then
    mkdir dist
fi

gcc "$1/main.c" -o "dist/$1"

if [ $? -eq 0 ]; then
    path=$""
    if [ -z "$2" ]; then
        path="./dist/$1"
    else
        # pass console arguments if those are set
        path="./dist/$1 $2"
    fi
    echo -e "Compilation successful. Executing at $path...\n\n\n"
    echo "---------------------------------------------------"
else
    echo "Compilation failed."
fi