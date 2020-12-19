#pragma once

#include <map>
#include <vector>

#include "tendril/hardwarerequestdata.hpp"

#include "lineside/pwitemdata.hpp"
#include "lineside/signalaspect.hpp"

namespace Lineside {

  //! Class for configuration data for BOPArray driven multiple aspect signal heads
  class BOPArrayMASHData : public PWItemData {
  public:
    BOPArrayMASHData();

    //! Information about the BOPArray
    Tendril::HardwareRequestData bopArrayRequest;

    //! Settings to map the BOPArray to the lights
    Tendril::SettingsMap settings;
    
    //! Extract the aspects
    std::map<SignalAspect,unsigned int> ExtractAspects() const;

    //! Extract the feathers
    std::vector<unsigned int> ExtractFeathers() const;
    
    virtual std::shared_ptr<PWItemModel> Construct(Tendril::HardwareManager& hw,
						   SoftwareManager& sw ) const override;
  };
}
