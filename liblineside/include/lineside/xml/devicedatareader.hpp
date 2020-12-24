#pragma once

#include <memory>
#include <xercesc/dom/DOMElement.hpp>
#include "tendril/devices/devicedata.hpp"

namespace Lineside::xml {
  //! Base class for reading in devices
  class DeviceDataReader {
  public:
    //! Common method for reading the name
    std::string
    ReadName(const xercesc::DOMElement *deviceDataElement) const;

    //! Checks if a given element is readable by an implementation
    virtual
    bool
    CheckReadableElement(const xercesc::DOMElement *element) const = 0;

    //! Read the device data
    virtual
    std::shared_ptr<Tendril::Devices::DeviceData>
    Read(const xercesc::DOMElement *deviceDataElement) const = 0;

    virtual ~DeviceDataReader() {}
  };
}
