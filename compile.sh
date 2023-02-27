#!/bin/bash

cd /home/chimas/sfml-car-cluster

# Configure and build the project
cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++ -S$(pwd) -B$(pwd)/build -G "Unix Makefiles"
cmake --build $(pwd)/build --config Release --target InstrumentClusterApplication -j $(nproc) --
