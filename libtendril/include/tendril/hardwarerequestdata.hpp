#pragma once

#include <string>

#include "tendril/tendriltypes.hpp"

namespace Tendril {
  //! Class to hold a request for a particular piece of hardware
  /*!
    The interpretation of the fields is heavily dependent on the
    type of hardware and the provider.
  */
  class HardwareRequestData {
  public:
    HardwareRequestData() :
      providerName("unset"),
      idOnProvider("unset"),
      settings() {}

    //! The name of the provider to request from the registrar
    std::string providerName;
    //! Identify the hardware on the provider (e.g. pin number)
    std::string idOnProvider;
    //! Provider dependent settings
    SettingsMap settings;
  };
}
