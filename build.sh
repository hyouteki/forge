#!/bin/bash

mkdir build
cd build
cmake ..
make -j4

cd ..
./forge
./clean.sh
