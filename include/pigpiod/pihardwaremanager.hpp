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

      virtual std::weak_ptr<BOPProviderRegistrar> GetBOPProviderRegistrar() override;
      virtual std::weak_ptr<BIPProviderRegistrar> GetBIPProviderRegistrar() override;
      virtual std::weak_ptr<PWMCProviderRegistrar> GetPWMCProviderRegistrar() override;
      
    private:
      std::shared_ptr<PiManager> piManager;
      std::shared_ptr<GPIOProvider> gpioProvider;
      std::shared_ptr<GPOutputProvider> gpOutputProvider;
    };
  }
}
