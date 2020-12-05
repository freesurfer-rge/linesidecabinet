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

    for( auto it : this->settings ) {
      auto key = it.first;
      auto value = it.second;

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
    const std::string featherString = "Feather";
    
    // Since feathers number from 1, always have one entry
    std::vector<unsigned int> result(1);

    std::map<unsigned int, unsigned int> foundFeathers;
    for( auto it : this->settings ) {
      auto key = it.first;
      auto value = it.second;

      if( key.find(featherString) != std::string::npos ) {
	auto featherIdStr = key.substr(featherString.size());
	unsigned int featherId = std::stoul(featherIdStr);

	if( featherId == 0 ) {
	  throw BadPWItemDataException(this->id, "Feather '0' defined");
	}

	foundFeathers[featherId] =  std::stoul(value);
      }
    }

    unsigned int expected = 1;    for( auto it : foundFeathers ) {
      if( it.first != expected ) {
	throw BadPWItemDataException(this->id, "Feathers are not sequential from one");
      }
      result.push_back(it.second);
      expected++;
    }
    
    return result;
  }

  
  std::shared_ptr<PWItemModel> BOPArrayMASHData::Construct(Tendril::HardwareManager& hw,
							   SoftwareManager& sw ) const {
    // Work around unused parameter warning
    this->UnusedSoftwareManager(sw);
    
    hw.bopArrayProviderRegistrar.Retrieve("GPIO");
    throw std::logic_error(__PRETTY_FUNCTION__);
  }
}
