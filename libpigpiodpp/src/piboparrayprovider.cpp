#include <string>

#include "pigpiodpp/pimanager.hpp"
#include "pigpiodpp/piboparray.hpp"

#include "pigpiodpp/piboparrayprovider.hpp"

namespace PiGPIOdpp {
  int PiBOPArrayProvider::getPi() const {
    return this->pi->getId();
  }

  std::unique_ptr<Tendril::BOPArray>
  PiBOPArrayProvider::GetHardware(const std::string& hardwareId,
				  const Tendril::SettingsMap& settings) {
    if( settings.size() == 0 ) {
      throw std::logic_error(hardwareId);
    }
    auto pinStrings = Tendril::BOPArray::ExtractPinList(settings);
    std::vector<unsigned int> pinIds;
    for( auto s : pinStrings ) {
      pinIds.push_back(std::stoul(s));
    }

    auto result = std::make_unique<PiBOPArray>(this->pi, pinIds);
    
    return result;
  }
}
