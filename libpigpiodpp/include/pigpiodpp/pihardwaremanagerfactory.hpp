#pragma once

#include "tendril/hardwaremanager.hpp"
#include "tendril/devices/i2cdevicedata.hpp"

namespace PiGPIOdpp {
  const std::string GPIO = "GPIO";
  
  std::shared_ptr<Tendril::HardwareManager>
  GetHardwareManager(const std::vector<Tendril::Devices::I2CDeviceData>& i2cDevices);
}
