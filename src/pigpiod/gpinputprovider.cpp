#include <sstream>

#include "pigpiod/gpinputprovider.hpp"

namespace Lineside {
  namespace PiGPIOd {
    GPInputProvider::GPInputProvider(std::shared_ptr<GPIOProvider> provider) :
      HardwareProvider<BinaryInputPin>(),
      gpioProvider(provider) {}

    
    std::unique_ptr<BinaryInputPin>
    GPInputProvider::GetHardware(const std::string& hardwareId,
				 const std::map<std::string,std::string>& settings) {
      unsigned char pinId = std::stoul(hardwareId);

      PiGPIOdpp::GPIOPull pull = PiGPIOdpp::GPIOPull::Off;
      unsigned int glitchMicroseconds = 0;
      PiGPIOdpp::GPIOEdge callBackEdge = PiGPIOdpp::GPIOEdge::Either;

      size_t settingsUsed = 0;
      if( settings.count(GPInputProvider::glitchSetting) == 1 ) {
	glitchMicroseconds = std::stoul(settings.at(GPInputProvider::glitchSetting));
	settingsUsed++;
      }

      if( settings.count(GPInputProvider::pudSetting) == 1 ) {
	pull = PiGPIOdpp::Parse<PiGPIOdpp::GPIOPull>(settings.at(GPInputProvider::pudSetting));
	settingsUsed++;
      }

      if( settings.size() != settingsUsed ) {
	std::stringstream msg;
	msg << __PRETTY_FUNCTION__
	    << ": Did not use all entries in settings";
	throw std::logic_error(msg.str());
      }
      
      return this->gpioProvider->GetGPInput(pinId, pull, glitchMicroseconds, callBackEdge);
    }
  }
}
