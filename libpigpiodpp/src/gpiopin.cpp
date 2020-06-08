#include <iostream>
#include <sstream>

#ifdef PIGPIODPP_HAVE_PIGPIO
#include <pigpiod_if2.h>
#else
#include "pigpiodpp/pigpiodstubs.hpp"
#endif

#include "pigpiodpp/pigpiodexceptions.hpp"

#include "pigpiodpp/gpiopin.hpp"


//! Trampoline function for callbacks
/*!
  This function exists to permit callbacks from the pigiod library into our code.
  It assumes that the userdata pointer is actually a pointer to an instance of GPIOPin.
 */
void CallBackTrampoline(int pi,
			unsigned user_gpio,
			unsigned level,
			uint32_t tick,void *userdata) {
  auto pin = static_cast<PiGPIOdpp::GPIOPin*>(userdata);
  pin->InvokeCallBack(pi, user_gpio, level, tick);
}


namespace PiGPIOdpp {
   
  GPIOPin::GPIOPin(const std::shared_ptr<PiManager> owner,
		   const unsigned int pinId) :
    pi(owner),
    pin(pinId),
    callBack(),
    callBackId(-1) {}
  
  GPIOPin::~GPIOPin() {
    if( this->callBackId >= 0 ) {
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
  
  void GPIOPin::SetPUDResistor(GPIOPull pull) {
    int libraryResult = set_pull_up_down(this->pi->getId(),
					 this->pin,
					   static_cast<unsigned>(pull));
    if( libraryResult != 0 ) {
      throw PiGPIOdException("set_pull_up_down", libraryResult);
    }    
  }
  
  void GPIOPin::SetGlitchFilter(unsigned int steadyMicroseconds) {
    int libraryResult = set_glitch_filter(this->pi->getId(),
					  this->pin,
					  steadyMicroseconds);
    if( libraryResult != 0 ) {
      throw PiGPIOdException("set_glitch_filter", libraryResult);
    } 
  }
  
  void GPIOPin::SetCallBack(GPIOEdge edge, CallBackFn f) {
    this->callBack = f;
    
    int libraryResult = callback_ex(this->pi->getId(),
				    this->pin,
				    static_cast<unsigned>(edge),
				    &CallBackTrampoline,
				    this);
    if( libraryResult < 0 ) {
      throw PiGPIOdException("callback_ex", libraryResult);
    }
    this->callBackId = libraryResult;
  }
  
  void GPIOPin::InvokeCallBack(int pi, unsigned user_gpio, unsigned level, uint32_t tick) {
    if( (pi != this->getPi()) || (user_gpio != this->getPin()) || (level > 2) ) {
      std::stringstream msg;
      msg << __FUNCTION__
	  << ": Got invalid args. "
	  << pi << " "
	  << user_gpio << " "
	  << level << " "
	  << tick;
      throw std::logic_error(msg.str());
    }
    
    // Note that we already checked for level > 2
    if( level < 2 ) {
      this->callBack(level);
    } else {
      std::clog << __FUNCTION__
		<< pi << " "
		<< user_gpio << " "
		<< "Level Unchanged" << std::endl;
    }
  }
}
