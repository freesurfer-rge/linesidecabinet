#include <xercesc/dom/DOMNodeList.hpp>

#include "xml/utilities.hpp"

#include "xml/i2cdevicedatareader.hpp"
#include "xml/i2cdevicelistreader.hpp"



namespace Lineside {
  namespace xml {
    bool I2CDeviceListReader::HasI2CDeviceList( const xercesc::DOMElement *parent ) const {
       if( !parent ) {
	throw std::logic_error("Bad parent");
      }

      return HasChildElement( parent, I2CDeviceListReader::ListElement );
    }

    xercesc::DOMElement* I2CDeviceListReader::GetI2CDeviceListElement( const xercesc::DOMElement *parent ) const {
      if( !parent ) {
	throw std::logic_error("Bad parent");
      }

      auto i2cDeviceListElement = Lineside::xml::GetSingleElementByName(parent, I2CDeviceListReader::ListElement );
      if( !i2cDeviceListElement ) {
	throw std::logic_error("Could not get element for I2CDevice list");
      }
      return i2cDeviceListElement;
    }

    std::vector<Lineside::I2CDeviceData> I2CDeviceListReader::Read( const xercesc::DOMElement *i2cDeviceListElement ) const {
      if( !i2cDeviceListElement ) {
	throw std::logic_error("Bad i2cDeviceListElement");
      }
      auto result = std::vector<Lineside::I2CDeviceData>();

      auto children = i2cDeviceListElement->getChildNodes();

      // Loop over children
      for( XMLSize_t i=0; i<children->getLength(); i++ ) {
	auto child = children->item(i);
	if( IsElementNode(child) ) {
	  auto element = dynamic_cast<xercesc::DOMElement*>(child);
	  
	  I2CDeviceDataReader reader;
	  if( reader.IsI2CDeviceElement( element ) ) {
	    auto nxt = reader.Read(element);
	    result.push_back(nxt);
	  }
	}
      }
      
      return result;
    }
  }
}
