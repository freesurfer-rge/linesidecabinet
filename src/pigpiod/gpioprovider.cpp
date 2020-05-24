#include <sstream>

#include "pigpiod/gpioprovider.hpp"
#include "linesideexceptions.hpp"

namespace Lineside {
  namespace PiGPIOd {
    GPIOProvider::GPIOProvider(std::shared_ptr<PiManager> piHardware) :
      pi(piHardware),
      allocatedPins() {}

    std::unique_ptr<GPOutput> GPIOProvider::GetGPOutput(const unsigned char pinId) {
      if( this->allocatedPins.count(pinId) != 0 ) {
	// Want to print as number, not character
	std::stringstream msg;
	msg << static_cast<int>(pinId);
	throw DuplicateKeyException(msg.str());
      }
      
      auto result = std::unique_ptr<GPOutput>(new GPOutput(this->pi->GetGPIOPin(pinId)));
      this->allocatedPins.insert(pinId);
      return result;
    }
  }
}
