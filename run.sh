#!/bin/bash

pushd /home/chimas/sfml-car-cluster

# Compile the program
./compile.sh

pushd build
make

# Run the program
./build/InstrumentCluster

popd
popd
