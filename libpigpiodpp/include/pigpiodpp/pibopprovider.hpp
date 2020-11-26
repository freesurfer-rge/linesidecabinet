#pragma once

#include <memory>

#include "tendril/binaryoutputpin.hpp"
#include "tendril/hardwareprovider.hpp"

namespace PiGPIOdpp {
  class PiManager;

  //! Provide output pins from Pi GPIO pins
  /*!
    Services requests for Tendril::BinaryOutputPin objects which control GPIO pins on the Pi.
   */
  class PiBOPProvider
    : public Tendril::HardwareProvider<Tendril::BinaryOutputPin> {
  public:
    PiBOPProvider(const std::shared_ptr<PiManager> owner)
      : pi(owner) {}

    //! Get the id of the controlled Pi
    int getPi() const;

    //! Get a GPIO pin as a Tendril::BinaryOutpuPin
    /*!
      Configures the given pin as an output pin.

      @param hardwareId The number of the required pin (must parse to an integer)
      @param settings Not supported. This map must be empty
     */
    virtual
    std::unique_ptr<Tendril::BinaryOutputPin>
    GetHardware(const std::string& hardwareId,
                const Tendril::SettingsMap& settings) override;
  private:
    std::shared_ptr<PiManager> pi;
  };
}
