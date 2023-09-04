@echo off
gcc -g csim.c -o csim
csim.exe   -v -s 2 -E 1 -b 4 -t traces/dave.trace