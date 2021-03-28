#pragma once

class CmdLineOpts {
public:
  CmdLineOpts() :
    helpMessagePrinted(false),
    clockPin(),
    dataPin(),
    latchPin()
  {}

  bool helpMessagePrinted;
  std::string wclkPin;
  std::string dataPin;
  std::string dclkPin;

  void Populate(int argc, char* argv[]);
};
