#pragma once

#include "tendril/hardwarerequestdata.hpp"
#include "tendril/devices/devicedata.hpp"

namespace Tendril::Devices {
  //! Class to hold data about an I2C device
  class BaseI2CDeviceData : public DeviceData {
  public:
    BaseI2CDeviceData() :
      DeviceData(),
      i2cCommsRequest() {}

    //! The request for the communicator
    HardwareRequestData i2cCommsRequest;
  };
}
