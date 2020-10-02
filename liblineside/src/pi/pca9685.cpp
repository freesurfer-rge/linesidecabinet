#include "lineside/pi/pca9685.hpp"


namespace Lineside {
  namespace Pi {
    PCA9685::PCA9685(const std::string deviceName,
		     const std::map<std::string,std::string> settings,
		     std::unique_ptr<PiGPIOdpp::I2CDevice> i2cCommunicator) :
      I2CDevice(std::move(i2cCommunicator), deviceName),
      Lineside::PWMCProvider() {
      std::cerr << __FUNCTION__ << ": " << settings.size() << std::endl;
    }
    
    void PCA9685::Register(HardwareManager& hwManager) {
      // Get a shared pointer and navigate around the types
      auto ptr = this->shared_from_this();
      auto ptrPCA9685 = std::dynamic_pointer_cast<PCA9685>(ptr);
      hwManager.pwmcProviderRegistrar.Register(this->name,
					       ptrPCA9685);
    }
  }
}
