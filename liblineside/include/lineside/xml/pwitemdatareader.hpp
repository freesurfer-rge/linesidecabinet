#pragma once

#include <memory>
#include <xercesc/dom/DOMElement.hpp>
#include "lineside/pwitemdata.hpp"

namespace Lineside {
  namespace xml {
    //! Base class for permanent way item readers
    class PWItemDataReader {
    public:
      //! Common method for reading the item id
      Lineside::ItemId
      ReadIdAttribute( const xercesc::DOMElement *pwItemElement ) const;

      //! Checks if a given element is readable by an implementation
      virtual bool MatchingElement( const xercesc::DOMElement *element ) const = 0;

      //! Read the permanent way item data
      virtual
      std::shared_ptr<Lineside::PWItemData>
      Read( const xercesc::DOMElement *pwItemElement ) const = 0;

      virtual ~PWItemDataReader() {}
    };
  }
}
