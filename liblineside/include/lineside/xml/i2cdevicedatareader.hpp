#pragma once

#include <stdexcept>
#include <iostream>
#include <xercesc/dom/DOMElement.hpp>

#include "tendril/devices/i2cdevicedata.hpp"

#include "lineside/xml/utilities.hpp"
#include "lineside/xml/devicedatareader.hpp"


namespace Lineside::xml {
  //! Class to read in data about a straightforward I2C Device
  /*!
    This should be used for anything which uses a plain
    I2CDeviceData<DeviceType> data structure
  */
  template<typename DeviceType>
  class I2CDeviceDataReader : public DeviceDataReader {
  public:
    I2CDeviceDataReader(const std::string tagName)
      : tagName(tagName) {}

    virtual
    bool
    CheckReadableElement(const xercesc::DOMElement *element) const override {
      if( !element ) {
	throw std::logic_error("Bad element");
      }
      // This could be more efficient, but works for now
      auto TAG_Device = StrToXMLCh(this->tagName);

      std::cout << __FUNCTION__ << ": " << XMLChToStr(element->getTagName()) << std::endl;

      return xercesc::XMLString::equals( element->getTagName(), TAG_Device.get() );
    }

    virtual
    std::shared_ptr<Tendril::Devices::DeviceData>
    Read(const xercesc::DOMElement *deviceDataElement) const override {
      if( deviceDataElement ) {
	throw std::logic_error("Not Implemented");
      }

      auto result = std::make_shared<Tendril::Devices::I2CDeviceData<DeviceType>>();

      return result;
    }

    const std::string tagName;
  };
}
