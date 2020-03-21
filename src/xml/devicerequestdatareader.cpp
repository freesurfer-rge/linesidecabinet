#include "xml/devicerequestdatareader.hpp"

namespace Lineside {
  namespace xml {
    Lineside::DeviceRequestData DeviceRequestDataReader::Read( const xercesc::DOMElement *deviceRequestElement ) const {
      if( !deviceRequestElement ) {
	throw std::logic_error("Bad deviceRequestElement ptr");
      }
      
      DeviceRequestData result;

      return result;
    }
  }
}
