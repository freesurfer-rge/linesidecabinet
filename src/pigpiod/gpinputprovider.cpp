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

      GPIOPull pull = GPIOPull::Off;
      unsigned int glitchMicroseconds = 0;
      GPIOEdge callBackEdge = GPIOEdge::Either;

      if( settings.count(GPInputProvider::glitchSetting) == 1 ) {
	glitchMicroseconds = std::stoul(settings.at(GPInputProvider::glitchSetting));
      }

      if( settings.count(GPInputProvider::pudSetting) == 1 ) {
	pull = Parse<GPIOPull>(settings.at(GPInputProvider::pudSetting));
      }
      
      return this->gpioProvider->GetGPInput(pinId, pull, glitchMicroseconds, callBackEdge);
    }
  }
}
