#include <xercesc/dom/DOMNodeList.hpp>

#include "xml/utilities.hpp"
#include "xml/settingsreader.hpp"

#include "xml/i2cdevicedatareader.hpp"

namespace Lineside {
  namespace xml {
    bool I2CDeviceDataReader::HasI2CDevice( const xercesc::DOMElement *parent ) const {
      if( !parent ) {
	throw std::logic_error("Bad parent ptr");
      }

      return HasChildElement(parent, this->I2CDeviceElement);
    }

    xercesc::DOMElement* I2CDeviceDataReader::GetI2CDeviceElement( const xercesc::DOMElement *parent ) const {
      if( !parent ) {
	throw std::logic_error("Bad parent ptr");
      }

      auto i2cDeviceElement = Lineside::xml::GetSingleElementByName(parent,
								    this->I2CDeviceElement );
      if( !i2cDeviceElement ) {
	throw std::logic_error("Bad I2CDevice element");
      }
      return i2cDeviceElement;
    }

    Lineside::I2CDeviceData I2CDeviceDataReader::Read( const xercesc::DOMElement *i2cDeviceElement ) const {
      if( !i2cDeviceElement ) {
	throw std::logic_error("Bad i2cDeviceElement ptr");
      }

      Lineside::I2CDeviceData result;

      // Read in the settings
      SettingsReader sr;
      if( sr.HasSettings( i2cDeviceElement ) ) {
	auto settingsElement = sr.GetSettingsElement(i2cDeviceElement);
	result.settings = sr.Read(settingsElement);
      }

      result.kind = GetAttributeByName( i2cDeviceElement, "kind" );
      result.bus = std::stoul( GetAttributeByName( i2cDeviceElement, "bus" ) );
      result.address = std::stoul( GetAttributeByName( i2cDeviceElement, "address"),
				   nullptr,
				   16 );
      result.name = GetAttributeByName( i2cDeviceElement, "name" );
      
      return result;
    }
  }
}
