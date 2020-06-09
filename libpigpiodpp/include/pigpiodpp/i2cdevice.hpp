#pragma once

#include "pigpiodpp/pimanager.hpp"

namespace PiGPIOdpp {
  //! Class for accessing an I2C device
  class I2CDevice {
  public:
    I2CDevice(const std::shared_ptr<PiManager> owner,
	      const unsigned int i2cBusId,
	      const unsigned int i2cBusAddress);
    
    ~I2CDevice();

    int getPi() const {
      return this->pi->getId();
    }

    unsigned int getI2CBus() const {
      return this->i2cBus;
    }

    unsigned int getI2CAddress() const {
      return this->i2cAddress;
    }

    int getHandle() const {
      return this->handle;
    }

  private:
    std::shared_ptr<PiManager> pi;
    const unsigned int i2cBus;
    const unsigned int i2cAddress;
    int handle;
  };
}
