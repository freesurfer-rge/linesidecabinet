#pragma once

#include "registrar.hpp"
#include "hardwareprovider.hpp"
#include "binaryoutputpin.hpp"
#include "binaryinputpin.hpp"
#include "pwmchannel.hpp"

namespace Lineside {
  //! Type for objects which supply binary output pins
  typedef HardwareProvider<BinaryOutputPin> BOPProvider;

  //! Type for objects which supply binary input pins
  typedef HardwareProvider<BinaryInputPin> BIPProvider;

  //! Type for objects which supply PWM channels
  typedef HardwareProvider<PWMChannel> PWMCProvider;

  //! Registrar for BOPProvider objects
  typedef Registrar<BOPProvider> BOPProviderRegistrar;

  //! Registrar for BIPProvider objects
  typedef Registrar<BIPProvider> BIPProviderRegistrar;

  //! Registrar for PWMCProvider objects
  typedef Registrar<PWMCProvider> PWMCProviderRegistrar;
  
  //! Abstract class for managing access to hardware
  class HardwareManager {
  public:
    HardwareManager() :
      bopProviderRegistrar(),
      bipProviderRegistrar(),
      pwmcProviderRegistrar() {}
    
    BOPProviderRegistrar bopProviderRegistrar;
    BIPProviderRegistrar bipProviderRegistrar;
    PWMCProviderRegistrar pwmcProviderRegistrar;
  };
}
