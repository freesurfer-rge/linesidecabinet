#pragma once

#include <map>

#include "pwitemdata.hpp"
#include "devicerequestdata.hpp"
#include "signalaspect.hpp"

namespace Lineside {
  class MultiAspectSignalHeadData : public PWItemData {
  public:
    MultiAspectSignalHeadData();

    std::map<SignalAspect,DeviceRequestData> aspectRequests;
    std::map<unsigned int,DeviceRequestData> featherRequests;
    
    void CheckData() const;
    
    virtual std::shared_ptr<PWItemModel> Construct( std::shared_ptr<HardwareManager> hw ) override;
  };
}
