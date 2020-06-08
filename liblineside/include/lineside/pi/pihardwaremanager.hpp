#pragma once
#include "pigpiodpp/pimanager.hpp"

#include "lineside/hardwaremanagerdata.hpp"
#include "lineside/hardwaremanager.hpp"

#include "lineside/pi/gpioprovider.hpp"

namespace Lineside {
  //! Namespace for holding hardware implementations for the Raspberry Pi
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
