#pragma once

#include <string>
#include <map>

namespace Lineside {
  template<typename Hardware>
  class HardwareProvider {
  public:
    typedef Hardware HardwareType;

    virtual ~HardwareProvider() {}

    virtual Hardware& GetHardware( const std::string& hardwareId,
				   const std::map<std::string,std::string>& settings ) = 0;
  };
}
