#!/bin/sh
cmake . -B build/
make -C build
./build/rayTracing

