#pragma once

class CmdLineOpts {
public:
  CmdLineOpts() :
    helpMessagePrinted(false),
    clockPin(),
    dataPin(),
    latchPin(),
    chainLength(-1) {}

  bool helpMessagePrinted;
  std::string clockPin;
  std::string dataPin;
  std::string latchPin;
  int chainLength;

  void Populate(int argc, char* argv[]);
};
