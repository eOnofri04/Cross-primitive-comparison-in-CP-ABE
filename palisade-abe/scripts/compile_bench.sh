#!/bin/bash

g++ -I/usr/local/include/palisade-abe -I/usr/local/include/palisade -I/usr/local/include/palisade/core -c -o bench128.o bench128.cpp

g++ -o bench128 -I/usr/local/include/palisade-abe -I/usr/local/include/palisade -I/usr/local/include/palisade/core -L/usr/local/lib bench128.cpp -lPALISADEabe -lPALISADEbinfhe -lPALISADEpke -lPALISADEcore
