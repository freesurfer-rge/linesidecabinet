#include "lineside/xml/utilities.hpp"

#include "lineside/xml/devicedatareader.hpp"

namespace Lineside::xml {
   std::string
   DeviceDataReader::ReadName(const xercesc::DOMElement *deviceDataElement) const {
     if( !deviceDataElement ) {
	throw std::logic_error("Bad deviceDataElement");
     }

     auto nameStr = GetAttributeByName(deviceDataElement, "name");
     return nameStr;
   }
}
