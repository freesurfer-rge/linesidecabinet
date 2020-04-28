#pragma once

#include <vector>

#include <xercesc/dom/DOMElement.hpp>

#include "i2cdevicedata.hpp"

namespace Lineside {
  namespace xml {
    //! Class to read in a list of I2C device data
    class I2CDeviceListReader {
    public:
      const std::string ListElement = "I2CDevices";

      bool HasI2CDeviceList( const xercesc::DOMElement *parent ) const;

      xercesc::DOMElement* GetI2CDeviceListElement( const xercesc::DOMElement *parent ) const;

      std::vector<Lineside::I2CDeviceData> Read( const xercesc::DOMElement *i2cDeviceListElement ) const;
    };
  }
}
