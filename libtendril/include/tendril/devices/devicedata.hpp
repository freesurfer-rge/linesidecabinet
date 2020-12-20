#pragma once
#include <string>

#include "tendril/tendriltypes.hpp"

namespace Tendril::Devices {
  const std::string NotConnected = "NotConnected";
  
  //! Base class for peripheral devices
  class DeviceData {
  public:
    DeviceData()
      : name("Uninitialised"),
	settings() {}
    
    std::string name;
    SettingsMap settings;
  };
}
