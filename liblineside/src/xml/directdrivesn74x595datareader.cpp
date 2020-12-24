#include <xercesc/dom/DOMNodeList.hpp>

#include "tendril/devices/directdrivesn74x595data.hpp"

#include "lineside/xml/utilities.hpp"
#include "lineside/xml/hardwarerequestdatareader.hpp"
#include "lineside/xml/settingsreader.hpp"
#include "lineside/xml/directdrivesn74x595datareader.hpp"

namespace Lineside::xml {
  const std::string DirectDriveSN74x595DataReader::TagName = "DirectDriveSN74x595";

  std::shared_ptr<Tendril::Devices::DeviceData>
  DirectDriveSN74x595DataReader::Read(const xercesc::DOMElement *deviceDataElement) const {
    if( !deviceDataElement ) {
      throw std::logic_error("Bad deviceDataElement");
    }

    // Get the name
    auto result = std::make_shared<Tendril::Devices::DirectDriveSN74x595Data>();
    result->name = this->ReadName(deviceDataElement);

    // Read the settings
    SettingsReader sr;
    if( sr.HasSettings(deviceDataElement) ) {
      auto se = sr.GetSettingsElement(deviceDataElement);
      result->settings = sr.Read(se);
    }

    // Read in the pins
    auto TAG_Pin = StrToXMLCh("Pin");
    const std::string BinaryOutput("BinaryOutput");

    auto children = deviceDataElement->getChildNodes();
    for( XMLSize_t i=0; i<children->getLength(); i++ ) {
      auto child = children->item(i);
      if( IsElementNode(child) ) {
	auto element = dynamic_cast<xercesc::DOMElement*>(child);
	
	if( xercesc::XMLString::equals( element->getTagName(), TAG_Pin.get() ) ) {
	  std::string nameStr = GetAttributeByName(element, "name");
	  auto bopElement = GetSingleElementByName(element, BinaryOutput);
	  HardwareRequestDataReader reader;

	  if( nameStr == "clock" ) {
	    result->clockPin = reader.Read(bopElement);
	  } else if( nameStr == "latch" ) {
	    result->latchPin = reader.Read(bopElement);
	  } else if( nameStr == "data" ) {
	    result->dataPin = reader.Read(bopElement);
	  } else if( nameStr == "clear" ) {
	    result->clearPin = reader.Read(bopElement);
	  } else if( nameStr == "enable" ) {
	    result->enablePin = reader.Read(bopElement);
	  } else {
	    std::stringstream msg;
	    msg << "Pin name of '"
		<< nameStr
		<< "' not recognised in DirectDriveSN74x595";
	    throw std::logic_error(msg.str());
	  }
	}
      }
    }
    
    return result;
  }
}
