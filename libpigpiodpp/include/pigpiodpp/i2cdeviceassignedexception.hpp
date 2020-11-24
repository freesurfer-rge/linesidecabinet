#pragma once

#include <stdexcept>

namespace PiGPIOdpp {
  //! Class for duplicate I2C devices
  class I2CDeviceAssignedException : public std::runtime_error {
  public:
    explicit I2CDeviceAssignedException(const unsigned int bus,
					const unsigned int device);

    const unsigned int busId;
    const unsigned int deviceId;
    std::string message;

    virtual const char* what() const noexcept override;
  };
}
