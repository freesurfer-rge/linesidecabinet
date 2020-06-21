#!/bin/bash
set echo
sudo apt-get install libjsonrpccpp-dev libjsonrpccpp-tools

sudo updatedb

locate version.h | grep json

echo
echo
cat /usr/include/jsonrpccpp/version.h
