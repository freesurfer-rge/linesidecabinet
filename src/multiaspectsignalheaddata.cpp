#include "multiaspectsignalheaddata.hpp"

#include "utility.hpp"

namespace Lineside {
  MultiAspectSignalHeadData::MultiAspectSignalHeadData() :
    PWItemData(),
    aspectRequests(),
    featherRequests() {}

  void MultiAspectSignalHeadData::CheckData() const {
    if( this->aspectRequests.count(SignalAspect::Red) != 1 ) {
      throw KeyNotFoundException(ToString(SignalAspect::Red));
    }
    if( this->aspectRequests.count(SignalAspect::Green) != 1 ) {
      throw KeyNotFoundException(ToString(SignalAspect::Green));
    }
    if( this->aspectRequests.count(SignalAspect::Yellow2) == 1 ) {
      if( this->aspectRequests.count(SignalAspect::Yellow1) != 1 ) {
	throw KeyNotFoundException(ToString(SignalAspect::Yellow1));
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
