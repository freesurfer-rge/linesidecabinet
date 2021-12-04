#include <stdexcept>

#include <xercesc/dom/DOMNodeList.hpp>

#include "lineside/xml/utilities.hpp"
#include "lineside/xml/settingsreader.hpp"

#include "lineside/xml/softwaremanagerdatareader.hpp"

namespace Lineside {
  namespace xml {
    bool SoftwareManagerDataReader::HasSoftwareManager( const xercesc::DOMElement *parent ) const {
      if( !parent ) {
	throw std::logic_error("Bad parent ptr");
      }

      return HasChildElement(parent, this->SoftwareManagerElement);
    }

    xercesc::DOMElement* SoftwareManagerDataReader::GetSoftwareManagerElement( const xercesc::DOMElement *parent ) const {
      if( !parent ) {
	throw std::logic_error("Bad parent ptr");
      }

      auto softwaremanagerElement = Lineside::xml::GetSingleElementByName(parent,
									  this->SoftwareManagerElement );
      if( !softwaremanagerElement ) {
	throw std::logic_error("Bad softwaremanager element");
      }
      return softwaremanagerElement;
    }

    Lineside::SoftwareManagerData SoftwareManagerDataReader::Read( const xercesc::DOMElement *softwaremanagerElement ) const {
      if( !softwaremanagerElement ) {
	throw std::logic_error("Bad softwaremanagerElement ptr");
      }

      Lineside::SoftwareManagerData result;

      // Read in the settings
      SettingsReader sr;
      if( sr.HasSettings( softwaremanagerElement ) ) {
	auto settingsElement = sr.GetSettingsElement(softwaremanagerElement);
	result.settings = sr.Read(settingsElement);
      }

      // Read in the other elements
      auto children = softwaremanagerElement->getChildNodes();

      auto TAG_rtc = StrToXMLCh(this->RTCElement);
      for( XMLSize_t i=0; i<children->getLength(); i++ ) {
	auto child = children->item(i);
	if( IsElementNode(child) ) {
	  auto element = dynamic_cast<xercesc::DOMElement*>(child);

	  // Check for RTC element
	  if( xercesc::XMLString::equals( element->getTagName(), TAG_rtc.get() ) ) {
	    result.rtcAddress = GetAttributeByName( element, "address" );
	    result.rtcPort = std::stoul(GetAttributeByName( element, "port" ));
	  } 
	}
      }
	
      return result;
    }
  }
}
