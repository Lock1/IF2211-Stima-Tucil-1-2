#!/bin/bash
gcc -Wall -Wextra -O3 -o bin/main src/main.c; strip -s bin/main
