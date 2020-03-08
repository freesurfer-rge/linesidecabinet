#include "trackcircuitmonitordata.hpp"

#include "utility.hpp"

namespace Lineside {
  std::shared_ptr<PWItemModel> TrackCircuitMonitorData::Construct( std::shared_ptr<HardwareManager> hw,
								   std::shared_ptr<SoftwareManager> sw ) const {
    if( !hw ) {
      throw std::logic_error("Bad hw ptr");
    }
    if( !sw ) {
      throw std::logic_error("Bad sw ptr");
    }

    LOCK_OR_THROW( bipProviderRegistrar, hw->GetBIPProviderRegistrar() );
    LOCK_OR_THROW( bipProvider,
		   bipProviderRegistrar->Retrieve( this->inputPinRequest.controller ) );
    auto bipWeak = bipProvider->GetHardware( this->inputPinRequest.controllerData,
					     this->inputPinRequest.settings );
    
    throw std::logic_error(__PRETTY_FUNCTION__);
  }
}
