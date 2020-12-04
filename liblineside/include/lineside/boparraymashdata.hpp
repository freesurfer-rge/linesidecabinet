#pragma once

#include <map>
#include <vector>

#include "lineside/pwitemdata.hpp"
#include "lineside/devicerequestdata.hpp"
#include "lineside/signalaspect.hpp"

namespace Lineside {

  //! Class for configuration data for BOPArray driven multiple aspect signal heads
  class BOPArrayMASHData : public PWItemData {
  public:
    BOPArrayMASHData();

    DeviceRequestData bopArrayRequest;
    
    //! Map from the aspects to pins in the array
    std::map<SignalAspect, unsigned int> aspectRequests;
    
    //! List of feather pins
    std::vector<unsigned int> featherRequests;
    
    //! Perform some basic sanity checks
    void CheckData() const;
    
    virtual std::shared_ptr<PWItemModel> Construct(Tendril::HardwareManager& hw,
						   SoftwareManager& sw ) const override;
  };
}
