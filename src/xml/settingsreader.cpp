#include <xercesc/dom/DOMNodeList.hpp>

#include "lineside/xml/utilities.hpp"

#include "lineside/xml/settingsreader.hpp"

namespace Lineside {
  namespace xml {
    bool SettingsReader::HasSettings( const xercesc::DOMElement *parent ) const {
      if( !parent ) {
	throw std::logic_error("Bad parent ptr");
      }

      return HasChildElement( parent, "Settings" );
    }
    
    xercesc::DOMElement* SettingsReader::GetSettingsElement( const xercesc::DOMElement *parent ) const {
      if( !parent ) {
	throw std::logic_error("Bad parent ptr");
      }

      auto settingsElement = Lineside::xml::GetSingleElementByName(parent, "Settings" );
      if( !settingsElement ) {
	throw std::logic_error("Bad Settings Element");
      }
      return settingsElement;
    }
    
    std::map<std::string,std::string> SettingsReader::Read( const xercesc::DOMElement *settingsElement ) const {
      if( !settingsElement ) {
	throw std::logic_error("Bad settingsElement ptr");
      }
      
      auto children = settingsElement->getChildNodes();

      auto TAG_Setting = StrToXMLCh("Setting");
      
      std::map<std::string,std::string> result;
      for( XMLSize_t i=0; i<children->getLength(); i++ ) {
	auto child = children->item(i);
	if( IsElementNode(child) ) {
	  auto element = dynamic_cast<xercesc::DOMElement*>(child);
	  
	  if( xercesc::XMLString::equals( element->getTagName(), TAG_Setting.get() ) ) {
	    std::string key = GetAttributeByName( element, "key" );
	    std::string value = GetAttributeByName( element, "value" );

	    result[key] = value;
	  } 
	}
      }
      return result;
    }
  }
}
