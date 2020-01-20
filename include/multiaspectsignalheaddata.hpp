#pragma once

#include <map>

#include "pwitemdata.hpp"
#include "devicerequestdata.hpp"
#include "signalaspect.hpp"

namespace Lineside {
  class BinaryOutputPin;
  class MultiAspectSignalHead;
  
  //! Class for configuration data for multiple aspect signal heads
  class MultiAspectSignalHeadData : public PWItemData {
  public:
    MultiAspectSignalHeadData();

    std::map<SignalAspect,DeviceRequestData> aspectRequests;
    std::map<unsigned int,DeviceRequestData> featherRequests;

    //! Perform some basic sanity checks
    void CheckData() const;
    
    virtual std::shared_ptr<PWItemModel> Construct( std::shared_ptr<HardwareManager> hw ) override;

  private:
    std::weak_ptr<BinaryOutputPin> FetchBOP( std::shared_ptr<HardwareManager> hw,
					     const DeviceRequestData& drd ) const;
    
    void PopulateAspects( std::shared_ptr<HardwareManager> hw,
			  std::shared_ptr<MultiAspectSignalHead> ) const;
  };
}
