#pragma once

#include "tendril/devices/devicedata.hpp"
#include "tendril/hardwarerequestdata.hpp"

namespace Tendril::Devices {
  class DirectDriveSN74x164Data : public DeviceData {
  public:
    const std::string chainLengthSetting = "chainLength";
    
    DirectDriveSN74x164Data()
      : DeviceData(),
	clockPin(),
	dataPin(),
	clearPin() {}
    
    void ConstructAndRegister(HardwareManager& hw) override;
    
    HardwareRequestData clockPin;
    HardwareRequestData dataPin;
    HardwareRequestData clearPin;
  };
}
