#include "lineside/xml/utilities.hpp"
#include "lineside/xml/settingsreader.hpp"

#include "lineside/xml/devicerequestdatareader.hpp"

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
      if( sr.HasSettings(deviceRequestElement) ) {
	auto settingsElement = sr.GetSettingsElement(deviceRequestElement);
	result.settings = sr.Read(settingsElement);
      }
	
      return result;
    }
  }
}
