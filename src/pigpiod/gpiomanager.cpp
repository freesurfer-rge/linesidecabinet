#include "pigpiod/pigpiodexceptions.hpp"

#include "pigpiod/gpiomanager.hpp"

#ifdef HAVE_PIGPIO
#include <pigpiod_if2.h>
#else
#include "pigpiod/pigpiodstubs.hpp"
#endif

namespace Lineside {
  namespace PiGPIOd {
    GPIOManager::GPIOManager(const std::shared_ptr<PiManager> owner) :
      pi(owner) {}

    void GPIOManager::SetMode(const unsigned int gpio, GPIOMode mode) {
      int libraryResult = set_mode(this->pi->getId(),
				   gpio,
				   static_cast<unsigned>(mode));
      if( libraryResult != 0 ) {
	throw PiGPIOdException("set_mode", libraryResult);
      }
    }
  }
}
