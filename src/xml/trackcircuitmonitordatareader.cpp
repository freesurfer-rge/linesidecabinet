#include "trackcircuitmonitordata.hpp"

#include "xml/utilities.hpp"
#include "xml/devicerequestdatareader.hpp"

#include "xml/trackcircuitmonitordatareader.hpp"

namespace Lineside {
  namespace xml {
    std::shared_ptr<Lineside::PWItemData> TrackCircuitMonitorDataReader::Read( const xercesc::DOMElement *pwItemElement ) const {
      if( !pwItemElement ) {
        throw std::logic_error("Bad pwItemElement");
      }
      auto result = std::make_shared<Lineside::TrackCircuitMonitorData>();

      result->id = this->ReadIdAttribute( pwItemElement );

      auto inputPinElement = GetSingleElementByName( pwItemElement, "BinaryInput" );

      DeviceRequestDataReader reader;
      result->inputPinRequest = reader.Read(inputPinElement);
      
      return result;
    }
  }
}
