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
}
