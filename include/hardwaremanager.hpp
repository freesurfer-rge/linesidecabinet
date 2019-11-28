#pragma once

#include "registrar.hpp"
#include "hardwareprovider.hpp"
#include "binaryoutputpin.hpp"
#include "binaryinputpin.hpp"
#include "pwmchannel.hpp"

namespace Lineside {
  //! Type for objects which supply binary output pins
  typedef HardwareProvider<BinaryOutputPin> BOPProvider;
  typedef HardwareProvider<BinaryInputPin> BIPProvider;
  typedef HardwareProvider<PWMChannel> PWMCProvider;
  
  typedef Registrar<BOPProvider> BOPProviderRegistrar;
  typedef Registrar<BIPProvider> BIPProviderRegistrar;
  typedef Registrar<PWMCProvider> PWMCProviderRegistrar;
  
  //! Abstract class for managing access to hardware
  class HardwareManager {
  public:
    virtual ~HardwareManager() {}

    virtual BOPProviderRegistrar* GetBOPProviderRegistrar() = 0;
    virtual BIPProviderRegistrar* GetBIPProviderRegistrar() = 0;
    virtual PWMCProviderRegistrar* GetPWMCProviderRegistrar() = 0;
  };
}
