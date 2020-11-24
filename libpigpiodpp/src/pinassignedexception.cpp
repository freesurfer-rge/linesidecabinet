#include <sstream>

#include "pigpiodpp/pinassignedexception.hpp"

namespace PiGPIOdpp {
  PinAssignedException::PinAssignedException(const unsigned int pin)
    : runtime_error(""),
      pinId(pin),
      message() {
    std::stringstream tmp;
    tmp << "Pin " << this->pinId << " is already assigned";
    this->message = tmp.str();
  }

  const char* PinAssignedException::what() const noexcept {
    return this->message.c_str();
  }
}
