#pragma once

#include <map>

#include "tendril/binaryoutputpin.hpp"
#include "tendril/hardwarerequestdata.hpp"

#include "lineside/pwitemdata.hpp"
#include "lineside/signalaspect.hpp"

namespace Lineside {
  class DirectDriveMASH;
  
  //! Class for configuration data for directly driven multiple aspect signal heads
  class DirectDriveMASHData : public PWItemData {
  public:
    DirectDriveMASHData();

    std::map<SignalAspect,Tendril::HardwareRequestData> aspectRequests;
    std::map<unsigned int,Tendril::HardwareRequestData> featherRequests;

    //! Perform some basic sanity checks
    void CheckData() const;
    
    virtual std::shared_ptr<PWItemModel> Construct(Tendril::HardwareManager& hw,
						   SoftwareManager& sw ) const override;

  private:
    std::unique_ptr<Tendril::BinaryOutputPin> FetchBOP(Tendril::HardwareManager& hw,
						       const Tendril::HardwareRequestData& drd ) const;
    
    void PopulateAspects(Tendril::HardwareManager& hw,
			 std::shared_ptr<DirectDriveMASH> target ) const;

    void PopulateFeathers(Tendril::HardwareManager& hw,
			  std::shared_ptr<DirectDriveMASH> target) const;
  };
}
