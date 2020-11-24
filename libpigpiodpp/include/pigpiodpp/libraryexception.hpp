#pragma once

#include <stdexcept>

namespace PiGPIOdpp {
  //! Class for exceptions from the underlying pigpiod library
  class LibraryException : public std::runtime_error {
  public:
    explicit LibraryException(const std::string calledMethod,
			      const int returnCode);
    
    const std::string methodName;
    const int errorCode;
    std::string message;
    
    virtual const char* what() const noexcept override;
  };
}
