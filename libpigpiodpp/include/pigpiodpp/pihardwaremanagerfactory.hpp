#pragma once

#include "tendril/hardwaremanagerfactory.hpp"

namespace PiGPIOdpp {
  class PiHardwareManagerFactory : Tendril::HardwareManagerFactory {
  public:
    const std::string GPIO = "GPIO";
    
    PiHardwareManagerFactory() {
      this->AddFactory(std::string("PiGPIOdpp"), this);
    }

    virtual std::shared_ptr<Tendril::HardwareManager>
    GetHardwareManager(const std::vector<Tendril::Devices::I2CDeviceData>& i2cDevices) override;
  };
}
