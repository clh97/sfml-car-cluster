#!/bin/bash

# THIS SCRIPT IS USED BY THE RASPBERRY PI TO RUN THE PROGRAM

pushd /home/chimas/sfml-car-cluster

# Compile the program
./compile.sh

pushd build
make

# Run the program
./InstrumentCluster

popd
popd
