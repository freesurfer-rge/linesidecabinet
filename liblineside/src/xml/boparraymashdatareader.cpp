#include <xercesc/dom/DOMNodeList.hpp>

#include "lineside/boparraymashdata.hpp"

#include "lineside/xml/utilities.hpp"
#include "lineside/xml/settingsreader.hpp"
#include "lineside/xml/devicerequestdatareader.hpp"

#include "lineside/xml/boparraymashdatareader.hpp"

namespace Lineside::xml {
  bool
  BOPArrayMASHDataReader::MatchingElement( const xercesc::DOMElement *element ) const {
    if( !element ) {
      throw std::logic_error("Bad element");
    }

    auto TAG_MASH = StrToXMLCh("BOPArrayMASH");
    
    return xercesc::XMLString::equals( element->getTagName(), TAG_MASH.get() );
  }

  std::shared_ptr<Lineside::PWItemData>
  BOPArrayMASHDataReader::Read( const xercesc::DOMElement *pwItemElement ) const {
    if( !pwItemElement ) {
      throw std::logic_error("Bad pwItemElement");
    }
    auto result = std::make_shared<Lineside::BOPArrayMASHData>();

    result->id = this->ReadIdAttribute( pwItemElement );

    SettingsReader sr;
    if( sr.HasSettings(pwItemElement) ) {
      auto settingsElement = sr.GetSettingsElement(pwItemElement);
      result->settings = sr.Read(settingsElement);
    }
    
    auto bopArrayElement = GetSingleElementByName( pwItemElement, "BOPArray" );

    DeviceRequestDataReader reader;
    result->bopArrayRequest = reader.Read(bopArrayElement);

    return result;
  }
}
