#ifdef HAVE_PIGPIO
#include <pigpiod_if2.h>
#else
#include "pigpiod/pigpiodstubs.hpp"
#endif

#include "pigpiod/pigpiodexceptions.hpp"

#include "pigpiod/gpiopin.hpp"


namespace Lineside {
  namespace PiGPIOd {
   
    GPIOPin::GPIOPin(const std::shared_ptr<PiManager> owner,
		     const unsigned int pinId) :
      pi(owner),
      pin(pinId) {}

    void  GPIOPin::SetMode(GPIOMode mode) {
      int libraryResult = set_mode(this->pi->getId(),
				   this->pin,
				   static_cast<unsigned>(mode));
      if( libraryResult != 0 ) {
	throw PiGPIOdException("set_mode", libraryResult);
      }
    }

    void GPIOPin::Write(const bool level) {
      int libraryResult = gpio_write(this->pi->getId(),
				     this->pin,
				     static_cast<unsigned>(level));
      if( libraryResult != 0 ) {
	throw PiGPIOdException("gpio_write", libraryResult);
      }
    }
  }
}
