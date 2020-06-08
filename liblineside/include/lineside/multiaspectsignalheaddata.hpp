#pragma once

#include <map>

#include "lineside/pwitemdata.hpp"
#include "lineside/devicerequestdata.hpp"
#include "lineside/signalaspect.hpp"

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
    
    virtual std::shared_ptr<PWItemModel> Construct(HardwareManager& hw,
						   SoftwareManager& sw ) const override;

  private:
    std::unique_ptr<BinaryOutputPin> FetchBOP(HardwareManager& hw,
					      const DeviceRequestData& drd ) const;
    
    void PopulateAspects(HardwareManager& hw,
			 std::shared_ptr<MultiAspectSignalHead> target ) const;

    void PopulateFeathers(HardwareManager& hw,
			  std::shared_ptr<MultiAspectSignalHead> target) const;
  };
}
