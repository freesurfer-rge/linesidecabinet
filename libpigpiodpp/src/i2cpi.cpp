#include <iostream>

#ifdef PIGPIODPP_HAVE_PIGPIO
#include <pigpiod_if2.h>
#else
#include "pigpiodstubs.hpp"
#endif

#include "pigpiodpp/pigpiodppexception.hpp"

#include "pigpiodpp/i2cpi.hpp"

namespace PiGPIOdpp {
  I2CPi::I2CPi(const std::shared_ptr<PiManager> owner,
	       const unsigned int i2cBusId,
	       const unsigned int i2cBusAddress) :
    I2CCommunicator(),
    pi(owner),
    i2cBus(i2cBusId),
    i2cAddress(i2cBusAddress),
    handle(-1) {
    const unsigned int NoOpenFlags = 0;
    this->handle = i2c_open(this->pi->getId(),
			    this->i2cBus,
			    this->i2cAddress,
			    NoOpenFlags);
    if( this->handle < 0 ) {
      throw PiGPIOdppException("i2c_open", this->handle);
    }
  }

  I2CPi::~I2CPi() {
    if( this->handle >= 0 ) {
      auto res = i2c_close(this->pi->getId(),
			   this->handle);
      if( res != 0 ) {
	// Can't throw from a destructor
	std::clog << __FUNCTION__
		  << ": i2c_close failed"
		  << std::endl;
      }
    }
  }

  void I2CPi::WriteByte(uint8_t targetRegister, uint8_t value) {
    auto libraryResult = i2c_write_byte_data(this->pi->getId(),
					     this->handle,
					     targetRegister,
					     value);
    if( libraryResult != 0 ) {
      throw PiGPIOdppException("i2c_write_byte_data", libraryResult);
    }
  }

  void I2CPi::WriteWord(uint8_t targetRegister, uint16_t value) {
    auto libraryResult = i2c_write_word_data(this->pi->getId(),
					     this->handle,
					     targetRegister,
					     value);
    if( libraryResult != 0 ) {
      throw PiGPIOdppException("i2c_write_byte_data", libraryResult);
    }
  }
}
