#pragma once

#include <memory>
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
    
    std::vector<std::shared_ptr<Tendril::Devices::DeviceData>> devices;
    SettingsMap settings;
  };
}
