#pragma once

#include <cstdint>
#include <map>
#include <string>

namespace Lineside {
  //! Class to hold data to construct a software manager
  class SoftwareManagerData {
  public:
    std::string rtcAddress;
    uint16_t rtcPort;
    std::map<std::string,std::string> settings;
  };
}
