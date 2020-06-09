#ifdef PIGPIODPP_HAVE_PIGPIO
#include <pigpiod_if2.h>
#else
#include "pigpiodpp/pigpiodstubs.hpp"
#endif

#include "pigpiodpp/pigpiodexceptions.hpp"

#include "pigpiodpp/i2cdevice.hpp"

namespace PiGPIOdpp {
  I2CDevice::I2CDevice(const std::shared_ptr<PiManager> owner,
		       const unsigned int i2cBusId,
		       const unsigned int i2cBusAddress) :
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
      throw PiGPIOdException("i2c_open", this->handle);
    }
  }

  I2CDevice::~I2CDevice() {
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

  void I2CDevice::WriteByte(uint8_t targetRegister, uint8_t value) {
    auto libraryResult = i2c_write_byte_data(this->pi->getId(),
					     this->handle,
					     targetRegister,
					     value);
    if( libraryResult != 0 ) {
      throw PiGPIOdException("i2c_write_byte_data", libraryResult);
    }
  }

  void I2CDevice::WriteWord(uint8_t targetRegister, uint16_t value) {
    auto libraryResult = i2c_write_word_data(this->pi->getId(),
					     this->handle,
					     targetRegister,
					     value);
    if( libraryResult != 0 ) {
      throw PiGPIOdException("i2c_write_byte_data", libraryResult);
    }
  }
}
