#include <xercesc/dom/DOMNodeList.hpp>

#include "lineside/xml/utilities.hpp"

#include "lineside/xml/i2cdevicedatareader.hpp"
#include "lineside/xml/directdrivesn74x595datareader.hpp"
#include "lineside/xml/devicelistreader.hpp"



namespace Lineside {
  namespace xml {
    bool DeviceListReader::HasDeviceList( const xercesc::DOMElement *parent ) const {
       if( !parent ) {
	throw std::logic_error("Bad parent");
      }

      return HasChildElement( parent, DeviceListReader::ListElement );
    }

    xercesc::DOMElement*
    DeviceListReader::GetDeviceListElement( const xercesc::DOMElement *parent ) const {
      if( !parent ) {
	throw std::logic_error("Bad parent");
      }

      auto deviceListElement = Lineside::xml::GetSingleElementByName(parent, DeviceListReader::ListElement );
      if( !deviceListElement ) {
	throw std::logic_error("Could not get element for Device list");
      }
      return deviceListElement;
    }

    std::vector<std::shared_ptr<Tendril::Devices::DeviceData>>
    DeviceListReader::Read( const xercesc::DOMElement *deviceListElement ) const {
      if( !deviceListElement ) {
	throw std::logic_error("Bad deviceListElement");
      }
      auto result = std::vector<std::shared_ptr<Tendril::Devices::DeviceData>>();

      std::vector<std::unique_ptr<DeviceDataReader>> readers;
      readers.push_back(std::make_unique<DirectDriveSN74x595DataReader>());
      
      auto children = deviceListElement->getChildNodes();

      // Loop over children
      for( XMLSize_t i=0; i<children->getLength(); i++ ) {
	auto child = children->item(i);
	if( IsElementNode(child) ) {
	  auto element = dynamic_cast<xercesc::DOMElement*>(child);

	  bool hadMatch = false;
	  for( auto r=readers.begin(); r!=readers.end(); ++r ) {
	    if( (*r)->CheckReadableElement(element) ) {
	      if( hadMatch ) {
		throw std::logic_error("Multiple matches for Device Readers");
	      }
	      hadMatch = true;
	      result.push_back( (*r)->Read(element) );
	    }
	  }
	}
      }
      
      return result;
    }
  }
}
