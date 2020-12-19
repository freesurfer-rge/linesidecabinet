#include "lineside/linesideexceptions.hpp"
#include "lineside/directdrivemashdata.hpp"

#include "lineside/directdrivemash.hpp"

namespace Lineside {
  DirectDriveMASHData::DirectDriveMASHData() :
    PWItemData(),
    aspectRequests(),
    featherRequests() {}
  
  void DirectDriveMASHData::CheckData() const {
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
  
  std::shared_ptr<PWItemModel>
  DirectDriveMASHData::Construct(Tendril::HardwareManager& hw,
				 SoftwareManager& sw ) const {
    // Work around unused parameter warning
    this->UnusedSoftwareManager(sw);
    
    this->CheckData();
    
    // Work around private constructor of the DirectDriveMASH
    struct enabler : public DirectDriveMASH {
    public:
      friend class DirectDriveMASHData;
      enabler(const ItemId id) : DirectDriveMASH(id) {}
    };
    auto result = std::make_shared<enabler>(this->id);
    
    this->PopulateAspects( hw, result );
    this->PopulateFeathers( hw, result );
    
    return result;
  }
  
  std::unique_ptr<Tendril::BinaryOutputPin>
  DirectDriveMASHData::FetchBOP(Tendril::HardwareManager& hw,
				const Tendril::HardwareRequestData& drd ) const {
    auto bopProvider = hw.bopProviderRegistrar.Retrieve(drd.providerName);
    return bopProvider->GetHardware( drd.idOnProvider, drd.settings );
  }
  
  void
  DirectDriveMASHData::PopulateAspects(Tendril::HardwareManager& hw,
				       std::shared_ptr<DirectDriveMASH> target ) const {
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
  
  void
  DirectDriveMASHData::PopulateFeathers(Tendril::HardwareManager& hw,
					std::shared_ptr<DirectDriveMASH> target ) const {
    // Calling from private method, so assume CheckData() has been called
    
    // The map is nicely sorted by the keys (which are unsigned ints)
    for( auto it = this->featherRequests.begin();
	 it != this->featherRequests.end();
	 ++it ) {
      target->feathers.push_back( this->FetchBOP( hw, it->second ) );
    }
  }
}
