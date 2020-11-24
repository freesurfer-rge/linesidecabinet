#pragma once

#include "tendril/i2ccommunicator.hpp"
#include "pigpiodpp/pimanager.hpp"

namespace PiGPIOdpp {
  //! Class for accessing an I2C device
  class I2CPi : public Tendril::I2CCommunicator {
  public:
    I2CPi(const std::shared_ptr<PiManager> owner,
	      const unsigned int i2cBusId,
	      const unsigned int i2cBusAddress);
    
    ~I2CPi();

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

    virtual void WriteByte(uint8_t targetRegister, uint8_t value) override;

    virtual void WriteWord(uint8_t targetRegister, uint16_t value) override;

  private:
    std::shared_ptr<PiManager> pi;
    const unsigned int i2cBus;
    const unsigned int i2cAddress;
    int handle;
  };
}
