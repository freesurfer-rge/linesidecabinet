#pragma once

#include <map>
#include <string>
#include <vector>

#include "i2cdevicedata.hpp"

namespace Lineside {
  //! Class to hold data for the hardware manager
  class HardwareManagerData {
  public:
    HardwareManagerData() :
      i2cDevices(),
      settings() {}
    
    std::vector<I2CDeviceData> i2cDevices;
    std::map<std::string,std::string> settings;
  };
}
