#include <algorithm>
#include <sstream>

#include "tendril/boparray.hpp"

namespace Tendril {
  void BOPArray::Set(const size_t i, const bool level) {
    this->pinState.at(i) = level;
  }

  /*!
    The settings for a BOPArray are expected to be of the form
    { "O":"GPIO10", "1":"GPIO03" ... }
    with the keys actually being sequential integers, and the
    values having meaning to the underlying device. Since
    these are binary outputs, there should be any other settings
    required.
   */
  std::vector<std::string>
  BOPArray::ExtractPinList(const SettingsMap& settings) {
    const std::string unsetPin = "MISSING PIN ID!!!!";
    std::vector<std::string> result(settings.size(), unsetPin);

    for( auto kvPair : settings ) {
      auto idx = std::stoul(kvPair.first);
      result.at(idx) = kvPair.second;
    }

    if( std::count(result.begin(), result.end(), unsetPin) != 0 ) {
      std::stringstream msg;
      msg << __FUNCTION__
	  << " : Failed to fill the pin list for a BOPArray";
      throw std::logic_error(msg.str());
    }
    
    return result;
  }
}
