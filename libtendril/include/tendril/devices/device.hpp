#pragma once

#include <string>
#include <memory>

#include "tendril/hardwaremanager.hpp"

namespace Tendril::Devices {
// False positive on enable_shared_from_this
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
  class Device : public std::enable_shared_from_this<Device> {
  public:
    Device(const std::string& deviceName)
      :name(deviceName) {}

    virtual ~Device() {}

    virtual void Register(HardwareManager& hwmanager) = 0;

    const std::string name;
  };
#pragma GCC diagnostic pop
}
