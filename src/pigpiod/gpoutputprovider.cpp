#include "pigpiod/gpoutputprovider.hpp"

namespace Lineside {
  namespace PiGPIOd {
    GPOutputProvider::GPOutputProvider(std::shared_ptr<GPIOProvider> provider) :
      HardwareProvider<BinaryOutputPin>(),
      gpioProvider(provider) {}

    
    std::shared_ptr<BinaryOutputPin>
    GPOutputProvider::GetHardware(const std::string& hardwareId,
				  const std::map<std::string,std::string>& settings) {
      if( settings.size() != 0 ) {
	throw std::logic_error("Settings not available for GPIO Output Pins");
      }

      unsigned char pinId = std::stoul(hardwareId);

      return this->gpioProvider->GetGPOutput(pinId);
    }
  }
}
