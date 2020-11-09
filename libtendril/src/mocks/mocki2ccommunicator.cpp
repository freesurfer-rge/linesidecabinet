#include "tendril/mocks/mocki2ccommunicator.hpp"

namespace Tendril::Mocks {
  void MockI2CCommunicator::WriteByte(const uint8_t targetRegister,
				      const uint8_t value) {
    this->lastRegister = targetRegister;
    this->lastWrite = 0; // Make sure everything else is removed
    this->lastWrite = value;
  }

  void MockI2CCommunicator::WriteWord(const uint8_t targetRegister,
				      const uint16_t value) {
    this->lastRegister = targetRegister;
    this->lastWrite = 0; // Make sure everything else is removed
    this->lastWrite = value;
  }
}
