#!/bin/bash

# Bash script to compile and run just because I'm too lazy to have to keep hitting up :)
gcc -pthread -o hellotriangle hellotriangle.c glad.c -lglfw -lGLU -lGL -lrt -ldl
./hellotriangle 

