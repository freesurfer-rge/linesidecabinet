#pragma once

#include <string>

class CmdLineOpts {
public:
  CmdLineOpts() :
    helpMessagePrinted(false),
    configFilePath(),
    device(),
    channel(255) {}

  bool helpMessagePrinted;
  std::string configFilePath;
  std::string device;
  unsigned int channel;

  void Populate(int argc, char* argv[]);
};
