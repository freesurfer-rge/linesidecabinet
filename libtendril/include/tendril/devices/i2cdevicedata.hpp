#pragma once

#include <cstdint>
#include <string>

#include "tendril/devices/devicedata.hpp"

namespace Tendril::Devices {
  //! Class to hold data about an I2C device
  class I2CDeviceData : public DeviceData {
  public:
    I2CDeviceData() :
      DeviceData(),
      kind("Uninitialised"),
      bus(65535),
      address(65535) {}

    std::string kind;
    std::uint16_t bus;
    std::uint16_t address;
  };
}
