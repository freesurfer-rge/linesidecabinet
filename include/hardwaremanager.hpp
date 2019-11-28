#pragma once

#include "registrar.hpp"
#include "hardwareprovider.hpp"
#include "binaryoutputpin.hpp"
#include "binaryinputpin.hpp"
#include "pwmchannel.hpp"

namespace Lineside {
  //! Abstract class for managing access to hardware
  class HardwareManager {
  public:
    typedef HardwareProvider<BinaryOutputPin> BOPProvider;
    typedef HardwareProvider<BinaryInputPin> BIPProvider;
    typedef HardwareProvider<PWMChannel> PWMCProvider;
    
    typedef Registrar<BOPProvider> BOPProvierRegistrar;
    typedef Registrar<BIPProvider> BIPProviderRegistrar;
    typedef Registrar<PWMCProvider> PWMCProviderRegistrar;
  };
}
