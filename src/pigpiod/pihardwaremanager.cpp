#include "pigpiod/gpinputprovider.hpp"
#include "pigpiod/gpoutputprovider.hpp"

#include "pigpiod/pihardwaremanager.hpp"


namespace Lineside {
  namespace PiGPIOd {
    PiHardwareManager::PiHardwareManager(const HardwareManagerData& data) :
      HardwareManager(),
      piManager(PiManager::CreatePiManager()),
      gpioProvider() {
      if( data.settings.size() != 0 ) {
	throw std::logic_error("Settings not supported for PiHardwareManager");
      }
      this->gpioProvider = std::make_shared<GPIOProvider>(this->piManager);

      auto gpOutputProvider = std::make_shared<GPOutputProvider>(this->gpioProvider);
      this->bopProviderRegistrar.Register(this->GPIO, gpOutputProvider);

      auto gpInputProvider = std::make_shared<GPInputProvider>(this->gpioProvider);
      this->bipProviderRegistrar.Register(this->GPIO, gpInputProvider);
    }
  }
}
