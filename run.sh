#!/bin/bash

# THIS SCRIPT IS USED BY THE RASPBERRY PI TO RUN THE PROGRAM

cd /home/chimas/sfml-car-cluster/build

make -j4

# Run the program
./InstrumentCluster
