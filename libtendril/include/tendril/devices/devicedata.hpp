#pragma once
#include <string>

#include "tendril/tendriltypes.hpp"
#include "tendril/hardwaremanager.hpp"

namespace Tendril::Devices {
  const std::string NotConnected = "NotConnected";
  
  //! Base class for peripheral devices
  class DeviceData {
  public:
    DeviceData()
      : name("Uninitialised"),
	settings() {}

    virtual ~DeviceData() {}

    virtual void ConstructAndRegister(HardwareManager& hw) = 0;
    
    std::string name;
    SettingsMap settings;
  };
}
