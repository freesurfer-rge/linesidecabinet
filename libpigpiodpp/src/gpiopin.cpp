#include <iostream>
#include <sstream>

#ifdef PIGPIODPP_HAVE_PIGPIO
#include <pigpiod_if2.h>
#else
#include "pigpiodstubs.hpp"
#endif

#include "pigpiodpp/libraryexception.hpp"
#include "pigpiodpp/pimanager.hpp"

#include "pigpiodpp/gpiopin.hpp"


//! Trampoline function for callbacks
/*!
  This function exists to permit callbacks from the pigiod library into our code.
  It assumes that the userdata pointer is actually a pointer to an instance of GPIOPin.
 */
void CallBackTrampoline(int pi,
			unsigned user_gpio,
			unsigned level,
			uint32_t tick,
			void *userdata) {
  auto pin = static_cast<PiGPIOdpp::GPIOPin*>(userdata);
  pin->TriggerNotifications(pi, user_gpio, level, tick);
}


namespace PiGPIOdpp {
   
  GPIOPin::GPIOPin(const std::shared_ptr<PiManager> owner,
		   const unsigned int pinId) :
    BinaryOutputPin(),
    BinaryInputPin(),
    pi(owner),
    pin(pinId),
    callBackId(-1) {}
  
  GPIOPin::~GPIOPin() {
    this->CancelCallback();
    // TODO Release the pin from the PiManager
  }
  
  int GPIOPin::getPi() const {
    return this->pi->getId();
  }
  
  void GPIOPin::SetMode(const GPIOMode mode) {
    int libraryResult = set_mode(this->pi->getId(),
				 this->pin,
				 static_cast<unsigned>(mode));
    if( libraryResult != 0 ) {
      throw LibraryException("set_mode", libraryResult);
    }

    if( mode == GPIOMode::Input ) {
      this->SetupCallback();
    } else {
      this->CancelCallback();
    }
  }
  
  bool GPIOPin::Get() const {
    int libraryResult = gpio_read(this->pi->getId(),
				  this->pin);
    if( libraryResult == PI_BAD_GPIO ) {
      throw LibraryException("gpio_read", libraryResult);
    }
    
    return static_cast<bool>(libraryResult);
  }
  
  void GPIOPin::Set(const bool level) {
    int libraryResult = gpio_write(this->pi->getId(),
				   this->pin,
				   static_cast<unsigned>(level));
    if( libraryResult != 0 ) {
      throw LibraryException("gpio_write", libraryResult);
    }
  }
  
  void GPIOPin::SetPUDResistor(GPIOPull pull) {
    int libraryResult = set_pull_up_down(this->pi->getId(),
					 this->pin,
					 static_cast<unsigned>(pull));
    if( libraryResult != 0 ) {
      throw LibraryException("set_pull_up_down", libraryResult);
    }    
  }
  
  void GPIOPin::SetGlitchFilter(unsigned int steadyMicroseconds) {
    int libraryResult = set_glitch_filter(this->pi->getId(),
					  this->pin,
					  steadyMicroseconds);
    if( libraryResult != 0 ) {
      throw LibraryException("set_glitch_filter", libraryResult);
    } 
  }
  
  void GPIOPin::TriggerNotifications(int pi,
				     unsigned user_gpio,
				     unsigned level,
				     uint32_t tick) {
    // No need to lock, since NotifyUpdate already does this
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
      this->NotifyUpdate(static_cast<bool>(level));
    } else {
      // level==2 means 'unchanged'
      std::clog << __FUNCTION__
		<< pi << " "
		<< user_gpio << " "
		<< "Level Unchanged" << std::endl;
    }
  }

  void GPIOPin::SetupCallback() {
    std::lock_guard<std::mutex> lock(this->notifyMutex);
    
    // Set up the notification callback
    int libraryResult = callback_ex(this->pi->getId(),
				    this->pin,
				    static_cast<unsigned>(GPIOEdge::Either),
				    &CallBackTrampoline,
				    this);
    if( libraryResult < 0 ) {
      throw LibraryException("callback_ex", libraryResult);
    }
    this->callBackId = libraryResult;
  }

  void GPIOPin::CancelCallback() {
    std::lock_guard<std::mutex> lock(this->notifyMutex);
    
    if( this->callBackId >= 0 ) {
      auto res = callback_cancel(this->callBackId);
      if( res != 0 ) {
	// Can't throw an exception from a destructor
	std::clog << __FUNCTION__
		  << ": callback_cancel failed to find "
		  << this->callBackId
		  << std::endl;
      }
      this->callBackId = -1;
    }
  }
}
