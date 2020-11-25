#pragma once

#include "tendril/hardwaremanager.hpp"
#include "tendril/hardwaremanagerdata.hpp"

namespace PiGPIOdpp {
  const std::string GPIO = "GPIO";
  
  std::shared_ptr<Tendril::HardwareManager>
  GetHardwareManager(const Tendril::HardwareManagerData& hwData);
}
