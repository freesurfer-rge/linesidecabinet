#pragma once

#include <set>

#include "pigpiod/pimanager.hpp"
#include "pigpiod/gpoutput.hpp"

namespace Lineside {
  namespace PiGPIOd {
    class GPIOProvider {
    public:
      GPIOProvider(std::shared_ptr<PiManager> piHardware);

      std::shared_ptr<GPOutput> GetGPOutput(const unsigned char pinId);
    private:
      std::shared_ptr<PiManager> pi;
      std::set<unsigned char> allocatedPins;
    };
  }
}
