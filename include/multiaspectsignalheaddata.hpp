#pragma once

#include <map>

#include "pwitemdata.hpp"
#include "devicerequestdata.hpp"
#include "signalaspect.hpp"
#include "signalstate.hpp"
#include "binaryoutputpin.hpp"

namespace Lineside {
  //! Class for configuration data for multiple aspect signal heads
  class MultiAspectSignalHeadData : public PWItemData {
  public:
    MultiAspectSignalHeadData();

    std::map<SignalAspect,DeviceRequestData> aspectRequests;
    std::map<unsigned int,DeviceRequestData> featherRequests;

    //! Perform some basic sanity checks
    void CheckData() const;

    std::multimap<SignalState,std::weak_ptr<BinaryOutputPin>> GenerateOutputStateMap( std::shared_ptr<HardwareManager> hw ) const;
    
    virtual std::shared_ptr<PWItemModel> Construct( std::shared_ptr<HardwareManager> hw ) override;
  };
}
