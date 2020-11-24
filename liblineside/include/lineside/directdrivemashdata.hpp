#pragma once

#include <map>

#include "tendril/binaryoutputpin.hpp"

#include "lineside/pwitemdata.hpp"
#include "lineside/devicerequestdata.hpp"
#include "lineside/signalaspect.hpp"

namespace Lineside {
  class DirectDriveMASH;
  
  //! Class for configuration data for multiple aspect signal heads
  class DirectDriveMASHData : public PWItemData {
  public:
    DirectDriveMASHData();

    std::map<SignalAspect,DeviceRequestData> aspectRequests;
    std::map<unsigned int,DeviceRequestData> featherRequests;

    //! Perform some basic sanity checks
    void CheckData() const;
    
    virtual std::shared_ptr<PWItemModel> Construct(Tendril::HardwareManager& hw,
						   SoftwareManager& sw ) const override;

  private:
    std::unique_ptr<Tendril::BinaryOutputPin> FetchBOP(Tendril::HardwareManager& hw,
						       const DeviceRequestData& drd ) const;
    
    void PopulateAspects(Tendril::HardwareManager& hw,
			 std::shared_ptr<DirectDriveMASH> target ) const;

    void PopulateFeathers(Tendril::HardwareManager& hw,
			  std::shared_ptr<DirectDriveMASH> target) const;
  };
}
