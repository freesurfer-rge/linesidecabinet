#pragma once

#include <map>
#include <string>
#include <vector>

#include "tendril/tendriltypes.hpp"
#include "tendril/devices/devicedata.hpp"

namespace Tendril {
  //! Class to hold data for the hardware manager
  class HardwareManagerData {
  public:
    HardwareManagerData() :
      devices(),
      settings() {}
    
    std::vector<Tendril::Devices::DeviceData> devices;
    SettingsMap settings;
  };
}
