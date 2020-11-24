#include <string>

#include "pigpiodpp/pimanager.hpp"
#include "pigpiodpp/gpiopin.hpp"

#include "pigpiodpp/pibopprovider.hpp"

namespace PiGPIOdpp {
  int PiBOPProvider::getPi() const {
    return this->pi->getId();
  }

  std::unique_ptr<Tendril::BinaryOutputPin>
  PiBOPProvider::GetHardware(const std::string& hardwareId,
			     const Tendril::SettingsMap& settings) {
    if( settings.size() != 0 ) {
      throw std::logic_error("Settings not available for GPIO output pins");
    }

    unsigned char pinId = std::stoul(hardwareId);

    auto result = this->pi->GetGPIOPin(pinId);
    result->SetMode(GPIOMode::Output);
    result->Set(false);

    return result;
  }
}
