#!/bin/bash

dest=$1
echo "Creating assigment in $dest"

mkdir -p $dest

COPIES="README.md CMakeLists.txt .gitignore Hello.cpp main.cpp"
SOLUTIONS="String.hpp String.cpp Value.hpp Value.cpp ValueVisitor.hpp JsonWriter.hpp JsonWriter.cpp FizzBuzz.hpp"

cp $COPIES $dest

for f in $SOLUTIONS; do
    ./remove_solution.py $f > $dest/$f
done
