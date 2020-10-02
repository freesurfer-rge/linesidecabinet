#pragma once

#include <memory>

#include "pigpiodpp/pimanager.hpp"
#include "lineside/pi/i2cdevice.hpp"
#include "lineside/i2cdevicedata.hpp"

namespace Lineside {
  namespace Pi {
    //! Class for building I2C devices
    class I2CDeviceFactory {
    public:
      std::shared_ptr<I2CDevice> Manufacture(PiGPIOdpp::PiManager& piManager,
					     const I2CDeviceData& data);
    };
  }
}
