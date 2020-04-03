#include "xml/utilities.hpp"

#include "xml/pwitemdatareader.hpp"

namespace Lineside {
  namespace xml {
    Lineside::ItemId PWItemDataReader::ReadIdAttribute( const xercesc::DOMElement *pwItemElement ) const {
      if( !pwItemElement ) {
	throw std::logic_error("Bad pwItemElement");
      }

      auto idStr = GetAttributeByName(pwItemElement, "id");

      Lineside::ItemId result;
      result.Parse(idStr);
      return result;
    }
  }
}
