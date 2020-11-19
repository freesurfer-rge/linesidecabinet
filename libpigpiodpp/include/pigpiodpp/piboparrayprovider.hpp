#pragma once

#include <memory>

#include "tendril/boparray.hpp"
#include "tendril/hardwareprovider.hpp"

namespace PiGPIOdpp {
  class PiManager;

  class PiBOPArrayProvider
    : public Tendril::HardwareProvider<Tendril::BOPArray> {
  public:
    PiBOPArrayProvider(const std::shared_ptr<PiManager> owner)
      : pi(owner) {}

    int getPi() const;
 
    virtual
    std::unique_ptr<Tendril::BOPArray>
    GetHardware(const std::string& hardwareId,
                const Tendril::SettingsMap& settings) override;
  private:
    std::shared_ptr<PiManager> pi;
  };
}
