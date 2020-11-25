#pragma once

#include "tendril/registrar.hpp"
#include "tendril/hardwareprovider.hpp"
#include "tendril/binaryoutputpin.hpp"
#include "tendril/binaryinputpin.hpp"
#include "tendril/boparray.hpp"
#include "tendril/pwmchannel.hpp"

namespace Tendril {
  //! Class for managing hardware
  class HardwareManager {
  public:
    HardwareManager() :
      bopProviderRegistrar(),
      bipProviderRegistrar(),
      bopArrayProviderRegistrar(),
      pwmcProviderRegistrar() {}

    //! Registrar for providers of binary output pins
    Registrar<HardwareProvider<BinaryOutputPin>> bopProviderRegistrar;

    //! Registrar for providers of binary input pins
    Registrar<HardwareProvider<BinaryInputPin>> bipProviderRegistrar;

    //! Registrar for providers of binary output pin arrays
    Registrar<HardwareProvider<BOPArray>> bopArrayProviderRegistrar;

    //! Registrar for providers of PWM channels
    Registrar<HardwareProvider<PWMChannel>> pwmcProviderRegistrar;
  };
}
