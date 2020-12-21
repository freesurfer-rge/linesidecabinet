#pragma once

#include "tendril/devices/devicedata.hpp"
#include "tendril/hardwarerequestdata.hpp"

namespace Tendril::Devices {
  class DirectDriveSN74x595Data : public DeviceData {
  public:
    const std::string chainLengthSetting = "chainLength";
    
    DirectDriveSN74x595Data()
      : DeviceData(),
	clockPin(),
	dataPin(),
	latchPin(),
	clearPin(),
	enablePin() {}
    
    void ConstructAndRegister(HardwareManager& hw) override;
    
    HardwareRequestData clockPin;
    HardwareRequestData dataPin;
    HardwareRequestData latchPin;
    HardwareRequestData clearPin;
    HardwareRequestData enablePin;
  };
}
