#!/bin/bash

g++ -std=c++11  -pthread -Wall -g -O2 -DSSL_LIB_INIT -I/openabe/deps/root/include -I/openabe/root/include "-I/usr/local/include"   -c -o benchBN382.o benchBN382.cpp

g++ -o benchBN382 -std=c++11  -pthread -Wall -g -O2 -DSSL_LIB_INIT -I/openabe/deps/root/include -I/openabe/root/include "-I/usr/local/include" -L/openabe/deps/root/lib -L/openabe/root/lib "-L/usr/local/lib" benchBN382.cpp -lcrypto -lrelic -lrelic_ec -lopenabe
