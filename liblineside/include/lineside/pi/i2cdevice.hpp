#pragma once

#include <memory>

#include "pigpiodpp/i2cdevice.hpp"

#include "lineside/hardwaremanager.hpp"

namespace Lineside {
  namespace Pi {
    //! Base class for implementing an I2C hardware provider
    class I2CDevice : std::enable_shared_from_this<I2CDevice> {
    public:
      I2CDevice(std::unique_ptr<PiGPIOdpp::I2CDevice> i2cCommunicator);

      virtual ~I2CDevice();

      virtual void Register(HardwareManager& hwManager) const = 0;

    protected:
      std::unique_ptr<PiGPIOdpp::I2CDevice> communicator;
    };
  }
}
