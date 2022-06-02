#!/bin/bash

# Bash script to compile and run just because I'm too lazy to have to keep hitting up :)
#g++ -pthread -o helloworld helloworld.c glad.c -lglfw -lGLU -lGL
#./helloworld
gcc -pthread -o helloworld helloworld.c glad.c -lglfw -lGLU -lGL -lrt -ldl
./helloworld 

