#pragma once

#include <stdexcept>


namespace PiGPIOdpp {
  //! Class for exceptions from the PiGPIOdpp library
  class PiGPIOdppException : public std::runtime_error {
  public:
    explicit PiGPIOdppException(const std::string calledMethod,
				const int returnCode);
    
    const std::string methodName;
    const int errorCode;
    std::string message;
    
    virtual const char* what() const noexcept override;
  };
}
