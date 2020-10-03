#include "lineside/pi/i2cdevice.hpp"


namespace Lineside {
  namespace Pi {
    I2CDevice::I2CDevice(std::unique_ptr<PiGPIOdpp::I2CDevice> i2cCommunicator,
			 const std::string& deviceName) :
      name(deviceName),
      communicator(std::move(i2cCommunicator)) {}

    I2CDevice::~I2CDevice() {}
  }
}
