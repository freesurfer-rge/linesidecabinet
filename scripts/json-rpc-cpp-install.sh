#!/bin/bash
set echo
# sudo apt-get install libjsonrpccpp-dev libjsonrpccpp-tools

# Install prereqs
sudo apt-get install libcurl-openssl-dev libmicrohttpd-dev libargtable2-dev libjsoncpp-dev libhiredis-dev

sudo updatedb

# Get the sources
cd /tmp
git clone https://github.com/cinemast/libjson-rpc-cpp.git

# Build
mkdir -p libjson-rpc-cpp/build
cd libjson-rpc-cpp/build
cmake ..
make -j 2

# Test
make test

# Install
sudo make install
sudo ldconfig
