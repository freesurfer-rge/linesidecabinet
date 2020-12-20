#include "tendril/devices/i2cdevicedata.hpp"

namespace Tendril::Devices {
  void I2CDeviceData::ConstructAndRegister(HardwareManager& hw) {
    auto tmp = hw.i2cCommProviderRegistrar.Retrieve(this->name);
    throw std::logic_error("Not Implemented - should use GetI2CComms not the provider too");
  }
}
