#!/usr/bin/bash
gcc ./anothermain.c ./tools.c -o another
./another > ./test.txt
tac test.txt
