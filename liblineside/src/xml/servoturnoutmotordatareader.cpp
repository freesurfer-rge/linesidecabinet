#include "lineside/servoturnoutmotordata.hpp"

#include "lineside/xml/utilities.hpp"
#include "lineside/xml/devicerequestdatareader.hpp"

#include "lineside/xml/servoturnoutmotordatareader.hpp"

namespace Lineside {
  namespace xml {
    bool ServoTurnoutMotorDataReader::MatchingElement( const xercesc::DOMElement *element ) const {
      if( !element ) {
	throw std::logic_error("Bad element");
      }

      auto TAG_ServoTurnoutMotor = StrToXMLCh("ServoTurnoutMotor");

      return xercesc::XMLString::equals( element->getTagName(), TAG_ServoTurnoutMotor.get() );
    }
    
    std::shared_ptr<Lineside::PWItemData> ServoTurnoutMotorDataReader::Read( const xercesc::DOMElement *pwItemElement ) const {
      if( !pwItemElement ) {
	throw std::logic_error("Bad pwItemElement");
      }
      auto result = std::make_shared<Lineside::ServoTurnoutMotorData>();

      result->id = this->ReadIdAttribute( pwItemElement );

      std::string attrValue;
      attrValue = GetAttributeByName( pwItemElement, "straight" );
      result->straight = std::stoi(attrValue);
      attrValue = GetAttributeByName( pwItemElement, "curved" );
      result->curved = std::stoi(attrValue);

      auto pwmChannelElement = GetSingleElementByName( pwItemElement, "PWMChannel" );

      DeviceRequestDataReader reader;
      result->pwmChannelRequest = reader.Read(pwmChannelElement);
      
      return result;
    }
  }
}
