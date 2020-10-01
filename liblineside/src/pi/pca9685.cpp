#include "lineside/pi/pca9685.hpp"


namespace Lineside {
  namespace Pi {
    void PCA9685::Register(HardwareManager& hwManager) {
      // Get a shared pointer and navigate around the types
      auto ptr = this->shared_from_this();
      auto ptrPCA9685 = std::dynamic_pointer_cast<PCA9685>(ptr);
      hwManager.pwmcProviderRegistrar.Register(this->controllerName,
					       ptrPCA9685);
    }
  }
}
