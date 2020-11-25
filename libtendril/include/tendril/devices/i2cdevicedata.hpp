#pragma once

#include <cstdint>
#include <map>
#include <string>

#include "tendril/tendriltypes.hpp"

namespace Tendril::Devices {
  //! Class to hold data about an I2C device
  class I2CDeviceData {
  public:
    I2CDeviceData() :
      kind("Uninitialised"),
      bus(65535),
      address(65535),
      name("Uninitialised"),
      settings() {}

    std::string kind;
    std::uint16_t bus;
    std::uint16_t address;
    std::string name;
    SettingsMap settings;
  };
}
