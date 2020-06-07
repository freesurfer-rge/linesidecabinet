#pragma once

#include <set>

#include "pigpiodpp/pimanager.hpp"
#include "pigpiod/gpoutput.hpp"
#include "pigpiod/gpinput.hpp"

namespace Lineside {
  namespace PiGPIOd {
    class GPIOProvider {
    public:
      GPIOProvider(std::shared_ptr<PiGPIOdpp::PiManager> piHardware);
      
      std::unique_ptr<GPOutput> GetGPOutput(const unsigned char pinId);
      std::unique_ptr<GPInput> GetGPInput(const unsigned char pinId,
					  const PiGPIOdpp::GPIOPull pull,
					  const unsigned int glitchSteadyMicroseconds,
					  const PiGPIOdpp::GPIOEdge callBackEdge);
    private:
      std::shared_ptr<PiGPIOdpp::PiManager> pi;
      std::set<unsigned char> allocatedPins;

      void ReservePin(const unsigned char pinId);
    };
  }
}
