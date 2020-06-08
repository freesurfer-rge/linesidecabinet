#include <xercesc/dom/DOMNodeList.hpp>

#include "lineside/multiaspectsignalheaddata.hpp"

#include "lineside/xml/utilities.hpp"
#include "lineside/xml/devicerequestdatareader.hpp"

#include "lineside/xml/multiaspectsignalheaddatareader.hpp"


namespace Lineside {
  namespace xml {
    bool MultiAspectSignalHeadDataReader::MatchingElement( const xercesc::DOMElement *element ) const {
      if( !element ) {
	throw std::logic_error("Bad element");
      }

      auto TAG_MASH = StrToXMLCh("MultiAspectSignalHead");

      return xercesc::XMLString::equals( element->getTagName(), TAG_MASH.get() );
    }
    
    std::shared_ptr<Lineside::PWItemData> MultiAspectSignalHeadDataReader::Read( const xercesc::DOMElement *pwItemElement ) const {
      if( !pwItemElement ) {
	throw std::logic_error("Bad pwItemElement");
      }
      auto result = std::make_shared<Lineside::MultiAspectSignalHeadData>();

      result->id = this->ReadIdAttribute( pwItemElement );

      auto TAG_Aspect = StrToXMLCh("Aspect");
      auto TAG_Feather = StrToXMLCh("Feather");
      const std::string BinaryOutput("BinaryOutput");

      auto children = pwItemElement->getChildNodes();
      for( XMLSize_t i=0; i<children->getLength(); i++ ) {
	auto child = children->item(i);
	if( IsElementNode(child) ) {
	  auto element = dynamic_cast<xercesc::DOMElement*>(child);
	  
	  if( xercesc::XMLString::equals( element->getTagName(), TAG_Aspect.get() ) ) {
	    std::string aspectStr = GetAttributeByName(element, "name");
	    auto aspect = Lineside::Parse<Lineside::SignalAspect>(aspectStr);

	    auto bopElement = GetSingleElementByName(element, BinaryOutput);
	    
	    DeviceRequestDataReader reader;
	    result->aspectRequests[aspect] = reader.Read(bopElement);
	  } else if ( xercesc::XMLString::equals( element->getTagName(), TAG_Feather.get() ) ) {
	    std::string routeStr = GetAttributeByName(element, "route");
	    unsigned int route = std::stoi(routeStr);

	    
	    auto bopElement = GetSingleElementByName(element, BinaryOutput);
	    
	    DeviceRequestDataReader reader;
	    result->featherRequests[route] = reader.Read(bopElement);
	  }
	}
      }
      
      return result;
    }
  }
}