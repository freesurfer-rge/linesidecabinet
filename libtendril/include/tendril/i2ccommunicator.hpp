#pragma once

#include <cstdint>

namespace Tendril {
  //! Class for communicating with an I2C device
  class I2CCommunicator {
  public:
    virtual ~I2CCommunicator() {};

    virtual void WriteByte(const uint8_t targetRegister,
			   const uint8_t value) = 0;

    virtual void WriteWord(const uint8_t targetRegister,
			   const uint16_t value) = 0;
  };
}
