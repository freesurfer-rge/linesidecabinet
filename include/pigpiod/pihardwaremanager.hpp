#pragma once

#include "hardwaremanagerdata.hpp"
#include "hardwaremanager.hpp"

#include "pigpiod/pimanager.hpp"
#include "pigpiod/gpioprovider.hpp"

namespace Lineside {
  namespace PiGPIOd {
    class PiHardwareManager : public HardwareManager {
    public:
      const std::string GPIO = "GPIO";
      
      PiHardwareManager(const HardwareManagerData& data);
      
    private:
      std::shared_ptr<PiManager> piManager;
      std::shared_ptr<GPIOProvider> gpioProvider;
    };
  }
}
