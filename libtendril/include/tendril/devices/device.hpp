#pragma once

#include <string>
#include <memory>

#include "tendril/hardwaremanager.hpp"

//! Namespace for holding peripheral devices
namespace Tendril::Devices {
  
// False positive on enable_shared_from_this
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
  //! Abstract class for all peripheral devices
  class Device : public std::enable_shared_from_this<Device> {
  public:
    Device(const std::string& deviceName)
      :name(deviceName) {}

    virtual ~Device() {}

    //! Register with a HardwareManager
    virtual void Register(HardwareManager& hwmanager) = 0;

    //! The name of this device (used in registering)
    const std::string name;
  };
#pragma GCC diagnostic pop
}
