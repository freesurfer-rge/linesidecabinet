#pragma once

#include <string>
#include <memory>

#include "pigpiodpp/i2cdevice.hpp"

#include "lineside/hardwaremanager.hpp"

namespace Lineside {
  namespace Pi {
    //! Base class for implementing an I2C hardware provider

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor" // False positive on enable_shared_from_this
    class I2CDevice : public std::enable_shared_from_this<I2CDevice> {
    public:
      I2CDevice(std::unique_ptr<PiGPIOdpp::I2CDevice> i2cCommunicator,
		const std::string& deviceName);

      virtual ~I2CDevice();

      virtual void Register(HardwareManager& hwManager) = 0;

      const std::string name;
    protected:
      std::unique_ptr<PiGPIOdpp::I2CDevice> communicator;
    };
#pragma GCC diagnostic pop
  }
}
