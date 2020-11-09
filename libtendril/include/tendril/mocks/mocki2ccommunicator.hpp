#pragma once

#include "tendril/i2ccommunicator.hpp"

namespace Tendril::Mocks {
  class MockI2CCommunicator : public I2CCommunicator {
  public:
    MockI2CCommunicator() :
      I2CCommunicator(),
      lastRegister(0),
      lastWrite(0) {}
    
    virtual void WriteByte(const uint8_t targetRegister,
			   const uint8_t value) override;

    virtual void WriteWord(const uint8_t targetRegister,
			   const uint16_t value) override;

    uint8_t lastRegister;
    uint32_t lastWrite;
  };
}
