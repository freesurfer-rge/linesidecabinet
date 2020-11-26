#pragma once

#include <string>
#include <memory>

#include "tendril/tendriltypes.hpp"

namespace Tendril {
  //! Abstraction of a provider of hardware access
  /*!
    The implementing library needs to provide concrete versions of this class for all supported types of hardware.

     \tparam Hardware The type of hardware which can be obtained from this provider
   */
  template<typename Hardware>
  class HardwareProvider {
  public:
    virtual ~HardwareProvider() {}

    //! Fetch hardware according to the given specification
    /*!
      Requests a piece of hardware (such as an input pin) from the provider.

      @param hardwareId A means of identifying the required piece of hardware. The exact meaning of this string depends on the implementation
      @param settings A collections of settings for the request. The exact meaning of these (or whether they are even supported) depends on the implementation
     */
    virtual
    std::unique_ptr<Hardware>
    GetHardware(const std::string& hardwareId,
		const SettingsMap& settings) = 0;
  };
}
