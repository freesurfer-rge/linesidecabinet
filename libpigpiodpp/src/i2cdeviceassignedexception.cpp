#include <sstream>

#include "pigpiodpp/i2cdeviceassignedexception.hpp"

namespace PiGPIOdpp {
  I2CDeviceAssignedException::I2CDeviceAssignedException(const unsigned int bus,
							 const unsigned int device)
    : runtime_error(""),
      busId(bus),
      deviceId(device) {
    std::stringstream tmp;
    tmp << "I2C device " << this->deviceId;
    tmp << " on bus " << this->busId;
    tmp << " is already assigned";
    this->message = tmp.str();
  }

  const char* I2CDeviceAssignedException::what() const noexcept {
    return this->message.c_str();
  }
}

