#include <stdexcept>

#include "lineside/xml/utilities.hpp"
#include "lineside/xml/settingsreader.hpp"

#include "lineside/xml/hardwarerequestdatareader.hpp"

namespace Lineside {
  namespace xml {
    Tendril::HardwareRequestData
    HardwareRequestDataReader::Read( const xercesc::DOMElement *hardwareRequestElement ) const {
      if( !hardwareRequestElement ) {
	throw std::logic_error("Bad hardwareRequestElement ptr");
      }
      
      Tendril::HardwareRequestData result;
      result.providerName = GetAttributeByName( hardwareRequestElement, "providerName" );
      result.idOnProvider = GetAttributeByName( hardwareRequestElement, "idOnProvider" );

      SettingsReader sr;
      if( sr.HasSettings(hardwareRequestElement) ) {
	auto settingsElement = sr.GetSettingsElement(hardwareRequestElement);
	result.settings = sr.Read(settingsElement);
      }
	
      return result;
    }
  }
}
