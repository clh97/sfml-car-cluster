#!/bin/bash

pushd /home/chimas/sfml-car-cluster

# Compile the program
./compile.sh

# Run the program
./build/InstrumentCluster

popd

