#include "xml/settingsreader.hpp"

namespace Lineside {
  namespace xml {
    std::map<std::string,std::string> SettingsReader::Read( const xercesc::DOMElement *parent ) const {
      if( !parent ) {
	throw std::logic_error("Bad parent ptr");
      }
      throw std::logic_error(__PRETTY_FUNCTION__);
    }
  }
}
