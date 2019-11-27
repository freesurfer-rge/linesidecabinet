#pragma once

#include "hardwareprovider.hpp"

namespace Lineside {
  template<typename Hardware>
  class HardwareProviderRegistrar {
  public:
    typedef Hardware HardwareType;

    HardwareProviderRegistrar() :
      providers() {}
  private:
    std::map<std::string,HardwareProvider<Hardware>&> providers;
  };
}
