#pragma once

#include "tendril/devices/device.hpp"
#include "tendril/devices/basei2cdevicedata.hpp"

namespace Tendril::Devices {
  //! Simple class for most I2C device data
  /*!
    If a device only communicates over the I2C bus (i.e. doesn't
    do anything like have a GPIO pin for signalling interrupts), then
    it can probably use this class for its data
   */
  template<typename DeviceType>
  class I2CDeviceData : public BaseI2CDeviceData {
  public:
    I2CDeviceData()
      : BaseI2CDeviceData() {
      static_assert(std::is_base_of<Device, DeviceType>::value,
		    "DeviceType must be derived from Tendril::Devices::Device");
    }

    virtual void ConstructAndRegister(HardwareManager& hw) override {
      auto i2cComm = hw.GetI2CComms(this->i2cCommsRequest);

      auto device = std::make_shared<DeviceType>(this->name,
						 this->settings,
						 i2cComm);

      device->Register(hw);
    }
  };
}
