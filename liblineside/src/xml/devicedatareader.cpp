#include "lineside/xml/utilities.hpp"

#include "lineside/xml/devicedatareader.hpp"

namespace Lineside::xml {
  bool
  DeviceDataReader::CheckReadableElement(const xercesc::DOMElement *element) const {
    if( !element ) {
      throw std::logic_error("Bad element");
    }
    // This could be more efficient, but works for now
    auto TAG_Device = StrToXMLCh(this->tagName);
    
    return xercesc::XMLString::equals( element->getTagName(), TAG_Device.get() );
  }
  
  std::string
  DeviceDataReader::ReadName(const xercesc::DOMElement *deviceDataElement) const {
    if( !deviceDataElement ) {
      throw std::logic_error("Bad deviceDataElement");
    }
    
    auto nameStr = GetAttributeByName(deviceDataElement, "name");
    return nameStr;
  }
}
