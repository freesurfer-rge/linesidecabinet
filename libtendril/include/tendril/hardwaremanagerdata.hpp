#pragma once

#include <map>
#include <string>
#include <vector>

#include "tendril/tendriltypes.hpp"
#include "tendril/devices/i2cdevicedata.hpp"

namespace Tendril {
  //! Class to hold data for the hardware manager
  class HardwareManagerData {
  public:
    HardwareManagerData() :
      i2cDevices(),
      settings() {}
    
    std::vector<Tendril::Devices::I2CDeviceData> i2cDevices;
    SettingsMap settings;
  };
}
