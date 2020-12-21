#pragma once

#include <memory>
#include <set>

#include "tendril/hardwareprovider.hpp"
#include "tendril/i2ccommunicator.hpp"

namespace PiGPIOdpp {
  class PiManager;

  //! Provide I2CCommunicators from the Pi
  class PiI2CCommsProvider
    : public Tendril::HardwareProvider<Tendril::I2CCommunicator> {
  public:
    PiI2CCommsProvider(const std::shared_ptr<PiManager> owner, const unsigned int busId)
      : pi(owner),
	busId(busId),
	assignedAddresses() {}

    //! Get the id of the controlled Pi
    int getPi() const;

    //! Get the controlled bus
    unsigned int getBusId() const;

    virtual
    std::unique_ptr<Tendril::I2CCommunicator>
    GetHardware(const std::string& hardwareId,
		const Tendril::SettingsMap& settings) override;
  private:
    std::shared_ptr<PiManager> pi;
    unsigned int busId;
    std::set<unsigned int> assignedAddresses;
  };
}
