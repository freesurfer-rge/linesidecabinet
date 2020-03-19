#include "xml/utilities.hpp"

#include "xml/settingsreader.hpp"

namespace Lineside {
  namespace xml {
    std::map<std::string,std::string> SettingsReader::Read( const xercesc::DOMElement *parent ) const {
      if( !parent ) {
	throw std::logic_error("Bad parent ptr");
      }

      auto settingsElement = Lineside::xml::GetSingleElementByName(parent, "Settings" );
      if( !settingsElement ) {
	throw std::logic_error("Bad settingsElement");
      }

      std::map<std::string,std::string> result;

      return result;
    }
  }
}
