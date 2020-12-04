#include <set>

#include "lineside/linesideexceptions.hpp"

#include "lineside/boparraymashdata.hpp"

namespace Lineside {
  BOPArrayMASHData::BOPArrayMASHData()
    : PWItemData(),
      bopArrayRequest(),
      settings() {}
  
  std::map<SignalAspect,unsigned int>
  BOPArrayMASHData::ExtractAspects() const {
    std::map<SignalAspect,unsigned int> result;

    std::set<std::string> pinValues;
    for( auto it : this->settings ) {
      auto key = it.first;
      auto value = it.second;

      if( pinValues.count(value) != 0 ) {
	auto msg = std::string("Pin already assigned: ") + value;
	throw BadPWItemDataException(this->id, msg);
      }
      pinValues.insert(value);

      SignalAspect aspect;
      if( TryParse(key, aspect) ) {
	if( result.count(aspect) != 0 ) {
	  std::string msg = std::string("Duplicate aspect: ") + key;
	  throw BadPWItemDataException(this->id, msg);
	}
	result[aspect] = std::stoul(value);;
      }
    }

    if( result.count(SignalAspect::Red) != 1 ) {
      std::string msg("Red aspect missing");
      throw BadPWItemDataException(this->id, msg);
    }
    if( result.count(SignalAspect::Green) != 1 ) {
      std::string msg("Green aspect missing");
      throw BadPWItemDataException(this->id, msg);
    }
    if( result.count(SignalAspect::Yellow2) == 1 ) {
      if( result.count(SignalAspect::Yellow1) != 1 ) {
	std::string msg("Have Yellow2 aspect but no Yellow1");
	throw BadPWItemDataException(this->id, msg);
      }
    }
    
    return result;
  }

  std::vector<unsigned int>
  BOPArrayMASHData::ExtractFeathers() const {
    throw std::logic_error(__PRETTY_FUNCTION__);
  }

  
  std::shared_ptr<PWItemModel> BOPArrayMASHData::Construct(Tendril::HardwareManager& hw,
							   SoftwareManager& sw ) const {
    // Work around unused parameter warning
    this->UnusedSoftwareManager(sw);
    
    hw.bopArrayProviderRegistrar.Retrieve("GPIO");
    throw std::logic_error(__PRETTY_FUNCTION__);
  }
}
