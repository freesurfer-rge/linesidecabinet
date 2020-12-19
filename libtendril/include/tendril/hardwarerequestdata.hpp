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
      controller("unset"),
      controllerData("unset"),
      settings() {}

    //! The name of the provider to request from the registrar
    std::string controller;
    //! Identify the hardware on the provider (e.g. pin number)
    std::string controllerData;
    //! Provider dependent settings
    SettingsMap settings;
  };
}
