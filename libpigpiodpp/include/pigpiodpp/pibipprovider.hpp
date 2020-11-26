#pragma once

#include <memory>
#include <string>

#include "tendril/binaryinputpin.hpp"
#include "tendril/hardwareprovider.hpp"

namespace PiGPIOdpp {
  class PiManager;

  //! Provide input pins from Pi GPIO pins
  /*!
    Services requests for Tendril::BinaryInputPin objects which monitor GPIO pins on the Pi.
   */
  class PiBIPProvider
    : public Tendril::HardwareProvider<Tendril::BinaryInputPin> {
  public:
    //! Setting key for setting the glitch filter provided by the <a href="http://abyz.me.uk/rpi/pigpio/pigpiod.html">pigpiod library</a>
    const std::string glitchSetting = "glitch";

    //! Setting key for controlling the pull up/pull down resistor on a GPIO pin
    const std::string pudSetting = "pud";
    
    PiBIPProvider(const std::shared_ptr<PiManager> owner)
      : pi(owner) {}

    //! Get the id of the controlled Pi
    int getPi() const;

    //! Get a GPIO pin as a Tendril::BinaryInputPin
    /*!
      Configures the given pin as an input pin.
      Currently, the supported keys in the settings are PiBIPProvider::glitchSetting and PiBIPProvider::pudSetting.

      @param hardwareId  The number of the required pin (must parse to an integer)
      @param settings Configuration for the input pin
     */
    virtual
    std::unique_ptr<Tendril::BinaryInputPin>
    GetHardware(const std::string& hardwareId,
                const Tendril::SettingsMap& settings) override;
  private:
    std::shared_ptr<PiManager> pi;
  };
}
