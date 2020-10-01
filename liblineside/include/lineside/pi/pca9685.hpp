#pragma once

#include <string>

#include "lineside/pi/i2cdevice.hpp"

namespace Lineside {
  namespace Pi {
    class PCA9685 : public I2CDevice, public Lineside::PWMCProvider {
    public:

      virtual void Register(HardwareManager& hwManager) override;
    private:
      std::string controllerName;
    };
  }
}
