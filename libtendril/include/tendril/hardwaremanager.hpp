#pragma once

#include "tendril/registrar.hpp"
#include "tendril/hardwareprovider.hpp"
#include "tendril/binaryoutputpin.hpp"
#include "tendril/binaryinputpin.hpp"
#include "tendril/boparray.hpp"
#include "tendril/pwmchannel.hpp"

namespace Tendril {
  //! Abstract class for managing hardware
  class HardwareManager {
  public:
    HardwareManager() :
      bopProviderRegistrar(),
      bipProviderRegistrar(),
      bopArrayProviderRegistrar(),
      pwmcProviderRegistrar() {}

    Registrar<HardwareProvider<BinaryOutputPin>> bopProviderRegistrar;
    Registrar<HardwareProvider<BinaryInputPin>> bipProviderRegistrar;
    Registrar<HardwareProvider<BOPArray>> bopArrayProviderRegistrar;
    Registrar<HardwareProvider<PWMChannel>> pwmcProviderRegistrar;
  };
}
