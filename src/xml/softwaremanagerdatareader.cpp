#include "xml/utilities.hpp"

#include "xml/settingsreader.hpp"
#include "xml/softwaremanagerdatareader.hpp"

namespace Lineside {
  namespace xml {
    bool SoftwareManagerDataReader::HasSoftwareManager( const xercesc::DOMElement *parent ) const {
      if( !parent ) {
	throw std::logic_error("Bad parent ptr");
      }

      return HasChildElement(parent, this->SoftwareManagerElement);
    }

    xercesc::DOMElement* SoftwareManagerDataReader::GetSoftwareManagerElement( const xercesc::DOMElement *parent ) const {
      if( !parent ) {
	throw std::logic_error("Bad parent ptr");
      }

      auto softwaremanagerElement = Lineside::xml::GetSingleElementByName(parent,
									  this->SoftwareManagerElement );
      if( !softwaremanagerElement ) {
	throw std::logic_error("Bad softwaremanager element");
      }
      return softwaremanagerElement;
    }

    Lineside::SoftwareManagerData SoftwareManagerDataReader::Read( const xercesc::DOMElement *softwaremanagerElement ) const {
      if( !softwaremanagerElement ) {
	throw std::logic_error("Bad softwaremanagerElement ptr");
      }

      Lineside::SoftwareManagerData result;


      return result;
    }
  }
}
