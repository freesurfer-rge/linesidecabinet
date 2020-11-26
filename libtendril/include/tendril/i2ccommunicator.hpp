#pragma once

#include <cstdint>

namespace Tendril {
  //! Class for communicating with an I2C device
  /*!
    This provides high level abstractions for interacting with I2C devices.
    Implementing libraries need to provide concrete instances.
   */
  class I2CCommunicator {
  public:
    virtual ~I2CCommunicator() {};

    //! Write a byte to the given register
    /*!
      @param targetRegister Which register should be written to
      @param value The value to be written
    */
    virtual void WriteByte(const uint8_t targetRegister,
			   const uint8_t value) = 0;

    //! Write a two byte word to the given register
    /*!
      @param targetRegister Which register should be written to
      @param value The value to be written
    */
    virtual void WriteWord(const uint8_t targetRegister,
			   const uint16_t value) = 0;
  };
}
