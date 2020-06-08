#pragma once

#include "hardwaremanagerdata.hpp"
#include "hardwaremanager.hpp"

#include "pigpiodpp/pimanager.hpp"
#include "pi/gpioprovider.hpp"

namespace Lineside {
  namespace Pi {
    class PiHardwareManager : public HardwareManager {
    public:
      const std::string GPIO = "GPIO";
      
      PiHardwareManager(const HardwareManagerData& data);
      
    private:
      std::shared_ptr<PiGPIOdpp::PiManager> piManager;
      std::shared_ptr<GPIOProvider> gpioProvider;
    };
  }
}
