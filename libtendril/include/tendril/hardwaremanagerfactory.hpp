#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "tendril/hardwaremanager.hpp"

#include "tendril/devices/i2cdevicedata.hpp"

namespace Tendril {
  class HardwareManagerFactory {
  public:
    static HardwareManagerFactory* GetFactory();

    virtual std::shared_ptr<HardwareManager>
    GetHardwareManager(const std::vector<Devices::I2CDeviceData>& i2cDevices) = 0;

    virtual ~HardwareManagerFactory() {}

  protected:
    void AddFactory(const std::string name, HardwareManagerFactory* factory);
    
  private:
    static std::map<std::string,HardwareManagerFactory*> factories;
  };
}
