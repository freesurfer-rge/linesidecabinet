#pragma once

#include <set>

#include "pigpiod/pimanager.hpp"
#include "pigpiod/gpoutput.hpp"
#include "pigpiod/gpinput.hpp"

namespace Lineside {
  namespace PiGPIOd {
    class GPIOProvider {
    public:
      GPIOProvider(std::shared_ptr<PiManager> piHardware);

      std::unique_ptr<GPOutput> GetGPOutput(const unsigned char pinId);
      std::unique_ptr<GPInput> GetGPInput(const unsigned char pinId,
					  const GPIOPull pull,
					  const unsigned int glitchSteadyMicroseconds,
					  const GPIOEdge callBackEdge);
    private:
      std::shared_ptr<PiManager> pi;
      std::set<unsigned char> allocatedPins;

      void ReservePin(const unsigned char pinId);
    };
  }
}
