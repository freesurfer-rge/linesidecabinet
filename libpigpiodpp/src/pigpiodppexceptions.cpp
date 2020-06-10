#include <sstream>

#ifdef PIGPIODPP_HAVE_PIGPIO
#include <pigpiod_if2.h>
#else
#include "pigpiodpp/pigpiodstubs.hpp"
#endif

#include "pigpiodpp/pigpiodppexception.hpp"

namespace PiGPIOdpp {
  PiGPIOdppException::PiGPIOdppException( const std::string calledMethod,
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

  const char* PiGPIOdppException::what() const noexcept {
    return this->message.c_str();
  }
}

