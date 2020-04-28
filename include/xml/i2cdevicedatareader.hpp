#pragma once

#include <xercesc/dom/DOMElement.hpp>

#include "i2cdevicedata.hpp"

namespace Lineside {
  namespace xml {
    //! Class to read in data about an I2C device
    class I2CDeviceDataReader {
    public:
      const std::string I2CDeviceElement = "I2CDevice";

      bool HasI2CDevice( const xercesc::DOMElement *parent ) const;

      bool IsI2CDeviceElement( const xercesc::DOMElement *element ) const;

      xercesc::DOMElement* GetI2CDeviceElement( const xercesc::DOMElement *parent ) const;

      Lineside::I2CDeviceData Read( const xercesc::DOMElement *i2cDeviceElement ) const;
    };
  }
}
