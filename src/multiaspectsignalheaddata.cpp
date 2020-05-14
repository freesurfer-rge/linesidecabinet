#include "multiaspectsignalheaddata.hpp"

#include "multiaspectsignalhead.hpp"
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

  std::shared_ptr<PWItemModel> MultiAspectSignalHeadData::Construct( std::shared_ptr<HardwareManager> hw,
								     std::shared_ptr<SoftwareManager> sw ) const {
    if( !hw ) {
      throw std::logic_error("Bad hw ptr");
    }
    if( !sw ) {
      throw std::logic_error("Bad sw ptr");
    }

    this->CheckData();

    // Work around private constructor of the MultiAspectSignalHead
    struct enabler : public MultiAspectSignalHead {
    public:
      friend class MultiAspectSignalHeadData;
      enabler(const ItemId id) : MultiAspectSignalHead(id) {}
    };
    auto result = std::make_shared<enabler>(this->id);

    this->PopulateAspects( hw, result );
    this->PopulateFeathers( hw, result );
    
    return result;
  }

  std::shared_ptr<BinaryOutputPin> MultiAspectSignalHeadData::FetchBOP( std::shared_ptr<HardwareManager> hw,
									const DeviceRequestData& drd ) const {
    LOCK_OR_THROW( bopProviderRegistrar, hw->GetBOPProviderRegistrar() );
    LOCK_OR_THROW( bopProvider,
		   bopProviderRegistrar->Retrieve(drd.controller) );
    return bopProvider->GetHardware( drd.controllerData, drd.settings );
  }
  
  void MultiAspectSignalHeadData::PopulateAspects( std::shared_ptr<HardwareManager> hw,
						   std::shared_ptr<MultiAspectSignalHead> target ) const {
    // Calling from private method, so can assume CheckData() has been called

    // Must have red and green aspects
    target->red = this->FetchBOP( hw, this->aspectRequests.at(SignalAspect::Red) );
    target->green = this->FetchBOP( hw, this->aspectRequests.at(SignalAspect::Green) );

    if( this->aspectRequests.count(SignalAspect::Yellow1) == 1 ) {
      target->yellow1 = this->FetchBOP( hw, this->aspectRequests.at(SignalAspect::Yellow1) );
      
      if( this->aspectRequests.count(SignalAspect::Yellow2) == 1 ) {
	target->yellow2 = this->FetchBOP( hw, this->aspectRequests.at(SignalAspect::Yellow2) );
      }
    }
  }

  void MultiAspectSignalHeadData::PopulateFeathers( std::shared_ptr<HardwareManager> hw,
						    std::shared_ptr<MultiAspectSignalHead> target ) const {
    // Calling from private method, so assume CheckData() has been called

    // The map is nicely sorted by the keys (which are unsigned ints)
    for( auto it = this->featherRequests.begin();
	 it != this->featherRequests.end();
	 ++it ) {
      target->feathers.push_back( this->FetchBOP( hw, it->second ) );
    }
  }
}
