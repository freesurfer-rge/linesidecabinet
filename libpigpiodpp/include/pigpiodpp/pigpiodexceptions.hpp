#pragma once

#include <stdexcept>
#include <sstream>

#ifdef HAVE_PIGPIO
#include <pigpiod_if2.h>
#else
#include "pigpiodpp/pigpiodstubs.hpp"
#endif

namespace PiGPIOdpp {
  //! Class for exceptions from the PiGPIOd library
  class PiGPIOdException : public std::runtime_error {
  public:
    explicit PiGPIOdException( const std::string calledMethod,
			       const int returnCode ) :
      std::runtime_error(""),
      methodName(calledMethod),
      errorCode(returnCode),
      message() {
      std::stringstream tmp;
      tmp << "Error from pigpiod on calling '" << this->methodName << "'. ";
      tmp << "Error code is '" << this->errorCode << "' ";
      tmp << "with explanation: " << pigpio_error(this->errorCode);
	this->message = tmp.str();
    }
    
    const std::string methodName;
    const int errorCode;
    std::string message;
      
    virtual const char* what() const noexcept override {
      return this->message.c_str();
    }
    
  };
}
