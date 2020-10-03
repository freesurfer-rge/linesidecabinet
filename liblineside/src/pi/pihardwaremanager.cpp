#include "lineside/pi/gpinputprovider.hpp"
#include "lineside/pi/gpoutputprovider.hpp"

#include "lineside/pi/pihardwaremanager.hpp"
#include "lineside/pi/i2cdevicefactory.hpp"

namespace Lineside {
  namespace Pi {
    PiHardwareManager::PiHardwareManager(const HardwareManagerData& data) :
      HardwareManager(),
      piManager(PiGPIOdpp::PiManager::CreatePiManager()),
      gpioProvider() {
      if( data.settings.size() != 0 ) {
	throw std::logic_error("Settings not supported for PiHardwareManager");
      }
      this->gpioProvider = std::make_shared<GPIOProvider>(this->piManager);

      auto gpOutputProvider = std::make_shared<GPOutputProvider>(this->gpioProvider);
      this->bopProviderRegistrar.Register(this->GPIO, gpOutputProvider);

      auto gpInputProvider = std::make_shared<GPInputProvider>(this->gpioProvider);
      this->bipProviderRegistrar.Register(this->GPIO, gpInputProvider);

      for( auto devData : data.i2cDevices ) {
	I2CDeviceFactory f;
	auto i2cDev = f.Manufacture( *(this->piManager), devData );

	i2cDev->Register(*this);
      }
    }
  }
}
