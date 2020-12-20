#pragma once

#include <vector>
#include <memory>

#include "tendril/hardwaremanager.hpp"
#include "tendril/devices/devicedata.hpp"

namespace Tendril::Devices {
  void CreateAndRegisterGPIODevices(const std::vector<std::shared_ptr<DeviceData>>& devices,
				    HardwareManager& hw);
}
