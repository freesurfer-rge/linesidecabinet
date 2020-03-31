#include <xercesc/dom/DOMNodeList.hpp>

#include "xml/utilities.hpp"

#include "xml/pwitemlistreader.hpp"

namespace Lineside {
  namespace xml {
    bool PWItemListReader::HasPWItemList( const xercesc::DOMElement *parent ) const {
      if( !parent ) {
	throw std::logic_error("Bad parent");
      }

      return HasChildElement( parent, PWItemListReader::ListElement );
    }
    
    xercesc::DOMElement* PWItemListReader::GetPWItemListElement( const xercesc::DOMElement *parent ) const {
      if( !parent ) {
	throw std::logic_error("Bad parent");
      }

      auto pwItemListElement = Lineside::xml::GetSingleElementByName(parent, PWItemListReader::ListElement );
      if( !pwItemListElement ) {
	throw std::logic_error("Could not get element for PWItem list");
      }
      return pwItemListElement;
    }
    
    std::vector<std::shared_ptr<Lineside::PWItemData>> PWItemListReader::Read( const xercesc::DOMElement *pwItemListElement ) const {
      if( !pwItemListElement ) {
	throw std::logic_error("Bad pwItemListElement");
      }
      auto result = std::vector<std::shared_ptr<Lineside::PWItemData>>();

      return result;
    }
  }
}
