#include <xercesc/dom/DOMNodeList.hpp>

#include "xml/utilities.hpp"

#include "xml/settingsreader.hpp"

namespace Lineside {
  namespace xml {
    std::map<std::string,std::string> SettingsReader::Read( const xercesc::DOMElement *parent ) const {
      if( !parent ) {
	throw std::logic_error("Bad parent ptr");
      }

      auto settingsElement = Lineside::xml::GetSingleElementByName(parent, "Settings" );
      if( !settingsElement ) {
	throw std::logic_error("Bad Settings Element");
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
