#include "tendril/devices/directdrivesn74x595.hpp"

namespace Tendril::Devices {
  void
  DirectDriveSN74x595::Register(HardwareManager& hwManager) {
    // Get a shared pointer and navigate around the types
    auto ptr = this->shared_from_this();
    auto ptr595 = std::dynamic_pointer_cast<DirectDriveSN74x595>(ptr);
    hwManager.bopArrayProviderRegistrar.Register(this->name,
						 ptr595);

  }

  void
  DirectDriveSN74x595::EnableOutputs(bool enable) {
    if( this->enablePin ) {
      // Recall that it's an active low enable
      this->enablePin->Set(!enable);
    } else {
      throw std::logic_error("Enable pin is not set for 74x595");
    }
  }
}
