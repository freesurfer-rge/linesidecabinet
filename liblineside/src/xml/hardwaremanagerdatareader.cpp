#include <xercesc/dom/DOMNodeList.hpp>

#include "lineside/xml/utilities.hpp"
#include "lineside/xml/settingsreader.hpp"
#include "lineside/xml/i2cdevicelistreader.hpp"

#include "lineside/xml/hardwaremanagerdatareader.hpp"

namespace Lineside {
  namespace xml {
    bool HardwareManagerDataReader::HasHardwareManager( const xercesc::DOMElement *parent ) const {
      if( !parent ) {
	throw std::logic_error("Bad parent ptr");
      }

      return HasChildElement(parent, this->HardwareManagerElement);
    }

    xercesc::DOMElement*
    HardwareManagerDataReader::GetHardwareManagerElement( const xercesc::DOMElement *parent ) const {
      if( !parent ) {
	throw std::logic_error("Bad parent ptr");
      }

      auto hardwaremanagerElement = Lineside::xml::GetSingleElementByName(parent,
									  this->HardwareManagerElement );
      if( !hardwaremanagerElement ) {
	throw std::logic_error("Bad hardwaremanager element");
      }
      return hardwaremanagerElement;
    }

    Tendril::HardwareManagerData
    HardwareManagerDataReader::Read( const xercesc::DOMElement *hardwaremanagerElement ) const {
      if( !hardwaremanagerElement ) {
	throw std::logic_error("Bad hardwaremanagerElement ptr");
      }
      
      Tendril::HardwareManagerData result;

      // Read in the list of I2CDevices
      I2CDeviceListReader i2cReader;
      if( i2cReader.HasI2CDeviceList( hardwaremanagerElement ) ) {
	auto i2cDeviceListElement = i2cReader.GetI2CDeviceListElement(hardwaremanagerElement);
	result.i2cDevices = i2cReader.Read(i2cDeviceListElement);
      }
      
      // Read in the settings
      SettingsReader sr;
      if( sr.HasSettings( hardwaremanagerElement ) ) {
	auto settingsElement = sr.GetSettingsElement(hardwaremanagerElement);
	result.settings = sr.Read(settingsElement);
      }
      
      return result;
    }
  }
}
