#pragma once

#include <memory>

#include "tendril/binaryoutputpin.hpp"
#include "tendril/hardwareprovider.hpp"

namespace PiGPIOdpp {
  class PiManager;
  
  class PiBOPProvider
    : public Tendril::HardwareProvider<Tendril::BinaryOutputPin> {
  public:
    PiBOPProvider(const std::shared_ptr<PiManager> owner)
      : pi(owner) {}

    int getPi() const;
    
    virtual
    std::unique_ptr<Tendril::BinaryOutputPin>
    GetHardware(const std::string& hardwareId,
                const Tendril::SettingsMap& settings) override;
  private:
    std::shared_ptr<PiManager> pi;
  };
}
