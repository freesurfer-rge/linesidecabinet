#include "multiaspectsignalheaddata.hpp"

#include "utility.hpp"

namespace Lineside {
  MultiAspectSignalHeadData::MultiAspectSignalHeadData() :
    PWItemData(),
    aspectRequests(),
    featherRequests() {}

  void MultiAspectSignalHeadData::CheckData() const {
    if( this->aspectRequests.count(SignalAspect::Red) != 1 ) {
      std::string msg("Red aspect missing");
      throw BadPWItemDataException(this->id, msg);
    }
    if( this->aspectRequests.count(SignalAspect::Green) != 1 ) {
      std::string msg("Green aspect missing");
      throw BadPWItemDataException(this->id, msg);
    }
    if( this->aspectRequests.count(SignalAspect::Yellow2) == 1 ) {
      if( this->aspectRequests.count(SignalAspect::Yellow1) != 1 ) {
	std::string msg("Have Yellow2 aspect but no Yellow1");
	throw BadPWItemDataException(this->id, msg);
      }
    }

    if( this->featherRequests.size() > 0 ) {
      if( this->featherRequests.count(0) != 0 ) {
	std::string msg("Feather '0' defined");
	throw BadPWItemDataException(this->id, msg);
      }

      unsigned int curr = 1;
      for( auto it=this->featherRequests.begin();
	   it!=this->featherRequests.end();
	   ++it ) {
	if( it->first != curr ) {
	  std::string msg("Feathers are not sequential from one");
	  throw BadPWItemDataException(this->id, msg);
	}
	curr++;
      }
    }
  }

  std::shared_ptr<PWItemModel> MultiAspectSignalHeadData::Construct( std::shared_ptr<HardwareManager> hw ) {
    if( !hw ) {
      throw std::logic_error("Bad hw ptr");
    }
    throw std::logic_error(__PRETTY_FUNCTION__);
  }
}
