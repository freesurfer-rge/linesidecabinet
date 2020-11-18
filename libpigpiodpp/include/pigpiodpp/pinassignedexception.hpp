#pragma once

#include <stdexcept>

namespace PiGPIOdpp {
  //! Exception for when an already assigned pin is requested
  class PinAssignedException : public std::runtime_error {
  public:
    explicit PinAssignedException(const unsigned int pin);

    const unsigned int pinId;

    std::string message;

    virtual const char* what() const noexcept override;
  };
}
