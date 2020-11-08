#pragma once

#include <string>
#include <map>
#include <memory>

namespace Tendril {
  typedef std::map<std::string,std::string> SettingsMap;
  
  //! Abstraction of a provider of hardware access
  template<typename Hardware>
  class HardwareProvider {
  public:
    virtual ~HardwareProvider() {}

    virtual
    std::unique_ptr<Hardware>
    GetHardware(const std::string& hardwareId,
		const SettingsMap& settings) = 0;
  };
}
