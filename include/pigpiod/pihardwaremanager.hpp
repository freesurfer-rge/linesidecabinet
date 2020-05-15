#pragma once

#include "hardwaremanagerdata.hpp"
#include "hardwaremanager.hpp"

#include "pigpiod/pimanager.hpp"
#include "pigpiod/gpioprovider.hpp"
#include "pigpiod/gpoutputprovider.hpp"

namespace Lineside {
  namespace PiGPIOd {
    class PiHardwareManager : public HardwareManager {
    public:
      PiHardwareManager(const HardwareManagerData& data);
      
    private:
      std::shared_ptr<PiManager> piManager;
      std::shared_ptr<GPIOProvider> gpioProvider;
      std::shared_ptr<GPOutputProvider> gpOutputProvider;
    };
  }
}
