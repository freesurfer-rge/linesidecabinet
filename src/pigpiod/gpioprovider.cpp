#include <sstream>

#include "pigpiod/gpioprovider.hpp"
#include "linesideexceptions.hpp"

namespace Lineside {
  namespace PiGPIOd {
    GPIOProvider::GPIOProvider(std::shared_ptr<PiGPIOdpp::PiManager> piHardware) :
      pi(piHardware),
      allocatedPins() {}

    std::unique_ptr<GPOutput> GPIOProvider::GetGPOutput(const unsigned char pinId) {
      this->ReservePin(pinId);
      return std::unique_ptr<GPOutput>(new GPOutput(this->pi->GetGPIOPin(pinId)));
    }
    
    std::unique_ptr<GPInput>
    GPIOProvider::GetGPInput(const unsigned char pinId,
			     const PiGPIOdpp::GPIOPull pull,
			     const unsigned int glitchSteadyMicroseconds,
			     const PiGPIOdpp::GPIOEdge callBackEdge) {
      this->ReservePin(pinId);
      return std::unique_ptr<GPInput>(new GPInput(this->pi->GetGPIOPin(pinId),
						  pull,
						  glitchSteadyMicroseconds,
						  callBackEdge));
    }
    
    void GPIOProvider::ReservePin(const unsigned char pinId) {
      if( this->allocatedPins.count(pinId) != 0 ) {
	// Want to print as number, not character
	std::stringstream msg;
	msg << static_cast<int>(pinId);
	throw DuplicateKeyException(msg.str());
      }
      this->allocatedPins.insert(pinId);
    }
  }
}
