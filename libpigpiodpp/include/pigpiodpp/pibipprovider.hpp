#pragma once

#include <memory>
#include <string>

#include "tendril/binaryinputpin.hpp"
#include "tendril/hardwareprovider.hpp"

namespace PiGPIOdpp {
  class PiManager;
  
  class PiBIPProvider
    : public Tendril::HardwareProvider<Tendril::BinaryInputPin> {
  public:
    const std::string glitchSetting = "glitch";
    const std::string pudSetting = "pud";
    
    PiBIPProvider(const std::shared_ptr<PiManager> owner)
      : pi(owner) {}

    int getPi() const;
    
    virtual
    std::unique_ptr<Tendril::BinaryInputPin>
    GetHardware(const std::string& hardwareId,
                const Tendril::SettingsMap& settings) override;
  private:
    std::shared_ptr<PiManager> pi;
  };
}
