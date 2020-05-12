#include "pigpiod/gpioprovider.hpp"


namespace Lineside {
  namespace PiGPIOd {
    GPIOProvider::GPIOProvider(std::shared_ptr<PiManager> piHardware) :
      pi(piHardware),
      allocatedPins() {}
  }
}
