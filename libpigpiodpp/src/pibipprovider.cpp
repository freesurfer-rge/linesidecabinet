#include <sstream>

#include "pigpiodpp/pimanager.hpp"
#include "pigpiodpp/gpiopin.hpp"

#include "pigpiodpp/pibipprovider.hpp"

namespace PiGPIOdpp {
  int PiBIPProvider::getPi() const {
    return this->pi->getId();
  }

  std::unique_ptr<Tendril::BinaryInputPin>
  PiBIPProvider::GetHardware(const std::string& hardwareId,
			     const Tendril::SettingsMap& settings) {
    unsigned char pinId = std::stoul(hardwareId);
    
    PiGPIOdpp::GPIOPull pull = PiGPIOdpp::GPIOPull::Off;
    unsigned int glitchMicroseconds = 0;

    size_t settingsUsed = 0;
    if( settings.count(this->glitchSetting) == 1 ) {
      glitchMicroseconds = std::stoul(settings.at(this->glitchSetting));
      settingsUsed++;
    }
    
    if( settings.count(this->pudSetting) == 1 ) {
      pull = PiGPIOdpp::Parse<PiGPIOdpp::GPIOPull>(settings.at(this->pudSetting));
      settingsUsed++;
    }
    
    if( settings.size() != settingsUsed ) {
      std::stringstream msg;
      msg << __PRETTY_FUNCTION__
	  << ": Did not use all entries in settings";
      throw std::logic_error(msg.str());
    }

    auto result = this->pi->GetGPIOPin(pinId);
    result->SetMode(GPIOMode::Input);
    result->SetPUDResistor(pull);
    result->SetGlitchFilter(glitchMicroseconds);

    return result;
  }
}
