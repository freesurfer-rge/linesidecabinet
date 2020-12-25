#pragma once

#include <vector>
#include <memory>

#include <xercesc/dom/DOMElement.hpp>

#include "tendril/devices/devicedata.hpp"

namespace Lineside {
  namespace xml {
    //! Class to read in a list of device data
    class DeviceListReader {
    public:
      const std::string ListElement = "Devices";

      bool HasDeviceList( const xercesc::DOMElement *parent ) const;

      xercesc::DOMElement*
      GetDeviceListElement( const xercesc::DOMElement *parent ) const;

      std::vector<std::shared_ptr<Tendril::Devices::DeviceData>>
      Read( const xercesc::DOMElement *deviceListElement ) const;
    };
  }
}
