#include <algorithm>
#include <sstream>

#include "tendril/boparray.hpp"

namespace Tendril {
  void BOPArray::Set(const size_t i, const bool level) {
    this->pinState.at(i) = level;
  }

  std::vector<std::string>
  BOPArray::ExtractPinList(const SettingsMap& settings) {
    const std::string unsetPin = "MISSING PIN ID!!!!";
    std::vector<std::string> result(settings.size(), unsetPin);

    for( auto kvPair : settings ) {
      auto idx = std::stoul(kvPair.first);
      if( idx >= settings.size() ) {
	std::stringstream msg;
	msg << __FUNCTION__
	    << "Index " << idx
	    << " too large for size " << settings.size();
	throw std::logic_error(msg.str());
      }
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
