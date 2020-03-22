#include "servoturnoutmotordata.hpp"

#include "xml/utilities.hpp"
#include "xml/devicerequestdatareader.hpp"

#include "xml/servoturnoutmotordatareader.hpp"

namespace Lineside {
  namespace xml {
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
