#ifdef HAVE_PIGPIO
#include <pigpiod_if2.h>
#else
#include "pigpiod/pigpiodstubs.hpp"
#endif

#include "pigpiod/pigpiodexceptions.hpp"

#include "pigpiod/gpiopin.hpp"


void CallBackTrampoline(int pi, unsigned user_gpio, unsigned level, uint32_t tick, void *userdata) {
  auto f = static_cast<Lineside::PiGPIOd::GPIOPin::CallBackFn*>(userdata);
  (*f)(pi, user_gpio, level, tick);
}


namespace Lineside {
  namespace PiGPIOd {
   
    GPIOPin::GPIOPin(const std::shared_ptr<PiManager> owner,
		     const unsigned int pinId) :
      pi(owner),
      pin(pinId),
      callBackId(-1) {}

    GPIOPin::~GPIOPin() {
      if( this->callBackId > 0 ) {
	auto res = callback_cancel(this->callBackId);
	if( res != 0 ) {
	  // Can't throw an exception from a destructor
	  std::clog << __FUNCTION__
		    << ": callback_cancel failed to find "
		    << this->callBackId
		    << std::endl;
	}
      }
    }

    void GPIOPin::SetMode(GPIOMode mode) {
      int libraryResult = set_mode(this->pi->getId(),
				   this->pin,
				   static_cast<unsigned>(mode));
      if( libraryResult != 0 ) {
	throw PiGPIOdException("set_mode", libraryResult);
      }
    }

    bool GPIOPin::Read() const {
      int libraryResult = gpio_read(this->pi->getId(),
				    this->pin);
      if( libraryResult == PI_BAD_GPIO ) {
	throw PiGPIOdException("gpio_read", libraryResult);
      }

      return static_cast<bool>(libraryResult);
    }

    void GPIOPin::Write(const bool level) {
      int libraryResult = gpio_write(this->pi->getId(),
				     this->pin,
				     static_cast<unsigned>(level));
      if( libraryResult != 0 ) {
	throw PiGPIOdException("gpio_write", libraryResult);
      }
    }

    void  GPIOPin::SetCallback(GPIOEdge edge, CallBackFn f) {
      this->callBack = f;

      int libraryResult = callback_ex(this->pi->getId(),
				      this->pin,
				      static_cast<unsigned>(edge),
				      &CallBackTrampoline,
				      &(this->callBack));
      if( libraryResult < 0 ) {
	throw PiGPIOdException("callback_ex", libraryResult);
      }
    }
  }
}
