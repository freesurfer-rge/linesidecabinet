#pragma once

#include <xercesc/dom/DOMElement.hpp>

#include "tendril/devices/devicedata.hpp"
#include "lineside/xml/devicedatareader.hpp"

namespace Lineside::xml {
  //! Class to read in data for a directly driven SN74x595
  class DirectDriveSN74x595DataReader : public DeviceDataReader {
  public:
    static const std::string TagName;
    
    DirectDriveSN74x595DataReader()
      : DeviceDataReader(DirectDriveSN74x595DataReader::TagName) {}

    virtual
    std::shared_ptr<Tendril::Devices::DeviceData>
    Read(const xercesc::DOMElement *deviceDataElement) const override;
  };
}
