#include <xercesc/dom/DOMNodeList.hpp>

#include "lineside/xml/utilities.hpp"
#include "lineside/xml/settingsreader.hpp"

#include "lineside/xml/i2cdevicedatareader.hpp"

namespace Lineside {
  namespace xml {
    bool I2CDeviceDataReader::HasI2CDevice( const xercesc::DOMElement *parent ) const {
      if( !parent ) {
	throw std::logic_error("Bad parent ptr");
      }

      return HasChildElement(parent, this->I2CDeviceElement);
    }

    bool I2CDeviceDataReader::IsI2CDeviceElement( const xercesc::DOMElement *element ) const {
      if( !element ) {
	throw std::logic_error("Bad element");
      }

      auto TAG_I2CDeviceData = StrToXMLCh(this->I2CDeviceElement);

      return xercesc::XMLString::equals( element->getTagName(), TAG_I2CDeviceData.get() );
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
