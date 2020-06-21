#!/bin/bash
set echo
# sudo apt-get install libjsonrpccpp-dev libjsonrpccpp-tools

# Install prereqs
sudo apt-get install libcurl4-openssl-dev libmicrohttpd-dev libargtable2-dev libjsoncpp-dev libhiredis-dev

echo
echo "Prerequisites installed"
echo

# Get the sources
cd /tmp
git clone https://github.com/cinemast/libjson-rpc-cpp.git

echo
echo "Fetched sources"
echo

# Configure
mkdir -p libjson-rpc-cpp/build
cd libjson-rpc-cpp/build
cmake ..

echo
echo "CMake configuration complete"
echo

# Build
make -j 2

echo
echo "Build complete"
echo

# Test
make test

echo
echo "Test complete"
echo

# Install
sudo make install
sudo ldconfig
