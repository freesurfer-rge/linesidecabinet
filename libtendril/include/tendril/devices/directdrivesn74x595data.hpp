#pragma once

#include "tendril/devices/devicedata.hpp"
#include "tendril/hardwarerequestdata.hpp"

namespace Tendril::Devices {
  class DirectDriveSN74x595Data : public DeviceData {
  public:
    DirectDriveSN74x595Data()
      : DeviceData(),
	clockPin(),
	dataPin(),
	latchPin(),
	clearPin(),
	enablePin() {}
    
    HardwareRequest clockPin;
    HardwareRequest dataPin;
    HardwareRequest latchPin;
    HardwareRequest clearPin;
    HardwareRequest enablePin;
  };
}
