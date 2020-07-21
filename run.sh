#!/bin/bash

llc $1.ll -o test.o -filetype=obj -relocation-model=pic
gcc $1.o
chmod +x a.out
./a.out