#pragma once

#include "tendril/i2ccommunicator.hpp"
#include "pigpiodpp/pimanager.hpp"

namespace PiGPIOdpp {
  //! Class for accessing an I2C device
  /*!
    Implements the Tendril::I2CCommunicator class using the <a href="http://abyz.me.uk/rpi/pigpio/pigpiod.html">pigpiod library</a>.
    This contains a pointer to the parent PiManager, to ensure that the library is not finalised until all communicators have been destroyed.
   */
  class I2CPi : public Tendril::I2CCommunicator {
  public:
    I2CPi(const std::shared_ptr<PiManager> owner,
	      const unsigned int i2cBusId,
	      const unsigned int i2cBusAddress);
    
    ~I2CPi();
    
    //! Get the id of the controlled Pi
    int getPi() const {
      return this->pi->getId();
    }

    //! Get the id of the associated I2C bus
    unsigned int getI2CBus() const {
      return this->i2cBus;
    }

    //! Get the I2C address of the target device
    unsigned int getI2CAddress() const {
      return this->i2cAddress;
    }

    //! The internal handle used by the <a href="http://abyz.me.uk/rpi/pigpio/pigpiod.html">pigpiod library</a>
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
