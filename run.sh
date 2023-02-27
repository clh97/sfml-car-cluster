#!/bin/bash

# THIS SCRIPT IS USED BY THE RASPBERRY PI TO RUN THE PROGRAM

pushd /home/chimas/sfml-car-cluster/build

make

# Run the program
./InstrumentCluster

popd
