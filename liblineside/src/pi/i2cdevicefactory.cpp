#include <sstream>

#include "lineside/pi/pca9685.hpp"

#include "lineside/pi/i2cdevicefactory.hpp"

namespace Lineside {
  namespace Pi {
    std::shared_ptr<I2CDevice>
    I2CDeviceFactory::Manufacture(PiGPIOdpp::PiManager& piManager,
				  const I2CDeviceData& data) {
      auto communicator = piManager.GetI2CDevice(data.bus, data.address);
      std::shared_ptr<I2CDevice> result;
      
      if( data.kind == "pca9685" ) {
	auto dev = std::make_shared<PCA9685>(data.name,
					     data.settings,
					     std::move(communicator));
	result = dev;
      } else {
	std::stringstream msg;
	msg << "Unrecognised I2C device: " << data.kind;
	throw std::logic_error(msg.str().c_str());
      }
      return result;
    }
  }
}
