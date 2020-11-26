#pragma once

#include <memory>

#include "tendril/boparray.hpp"
#include "tendril/hardwareprovider.hpp"

namespace PiGPIOdpp {
  class PiManager;

  //! Provide BOPArray objects from Pi GPIO pins
  /*
    Services requests for BOPArray objects which control GPIO pins on the Pi.
   */
  class PiBOPArrayProvider
    : public Tendril::HardwareProvider<Tendril::BOPArray> {
  public:
    PiBOPArrayProvider(const std::shared_ptr<PiManager> owner)
      : pi(owner) {}

    //! Get the id of the controlled Pi
    int getPi() const;

    //! Get a BOPArray from the GPIO pins
    /*!
      Configures the given pins as a Tendril::BOPArray.
      The settings map is processed using Tendril::BOPArray::ExtractPinList, which expects the keys to be parseable to sequential integers (starting from zero).
      As such, the resultant array of output pins will be equal in size to this map.
      The values from the map should also parseable to integers, and are used to select GPIO pins on the Pi.

      @param hardwareId Ignored (will be provided in message if an exception is thrown)
      @param settings Map of array location to pin id
     */
    virtual
    std::unique_ptr<Tendril::BOPArray>
    GetHardware(const std::string& hardwareId,
                const Tendril::SettingsMap& settings) override;
  private:
    std::shared_ptr<PiManager> pi;
  };
}
