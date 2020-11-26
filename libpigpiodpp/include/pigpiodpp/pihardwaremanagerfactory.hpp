#pragma once

#include "tendril/hardwaremanager.hpp"
#include "tendril/hardwaremanagerdata.hpp"

namespace PiGPIOdpp {
  //! String used to select the GPIO device (for input and output pin providers)
  const std::string GPIO = "GPIO";

  //! Construct and populate a Tendril::HardwareManager using the <a href="http://abyz.me.uk/rpi/pigpio/pigpiod.html">pigpiod library</a>
  /*!
    The resultant Tendril::HardwareManager will have providers registered under the key PiGPIOdpp::GPIO for binary input pins, binary output pins, and binary output pin arrays.
    In addition, any I2C devices specified in the hwData argument will be configured and registered.

    The settings member of the hwData argument is not currently supported, and must be left empty.
   */
  std::shared_ptr<Tendril::HardwareManager>
  GetHardwareManager(const Tendril::HardwareManagerData& hwData);
}
