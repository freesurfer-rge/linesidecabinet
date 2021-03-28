#pragma once

class CmdLineOpts {
public:
  CmdLineOpts() :
    helpMessagePrinted(false),
    wclkPin(),
    dataPin(),
    dclkPin()
  {}

  bool helpMessagePrinted;
  std::string wclkPin;
  std::string dataPin;
  std::string dclkPin;

  void Populate(int argc, char* argv[]);
};
