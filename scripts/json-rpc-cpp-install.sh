#!/bin/bash
set echo
sudo apt-get install libjsonrpccpp-dev libjsonrpccpp-tools

sudo updatedb

locate version.h | grep json
