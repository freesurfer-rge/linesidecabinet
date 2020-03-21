#include "xml/utilities.hpp"
#include "xml/settingsreader.hpp"

#include "xml/devicerequestdatareader.hpp"

namespace Lineside {
  namespace xml {
    Lineside::DeviceRequestData DeviceRequestDataReader::Read( const xercesc::DOMElement *deviceRequestElement ) const {
      if( !deviceRequestElement ) {
	throw std::logic_error("Bad deviceRequestElement ptr");
      }
      
      DeviceRequestData result;
      result.controller = GetAttributeByName( deviceRequestElement, "controller" );
      result.controllerData = GetAttributeByName( deviceRequestElement, "controllerData" );

      SettingsReader sr;
      auto settingsElement = sr.GetSettingsElement(deviceRequestElement);
      result.settings = sr.Read(settingsElement);
      
      return result;
    }
  }
}
