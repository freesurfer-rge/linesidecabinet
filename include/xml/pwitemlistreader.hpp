#pragma once

#include <vector>
#include <memory>
#include <string>

#include <xercesc/dom/DOMElement.hpp>

#include "pwitemdata.hpp"

namespace Lineside {
  namespace xml {
    //! Class for reading in a list of permanent way items
    class PWItemListReader {
    public:
      //! String to identify the starting element
      const std::string ListElement = std::string("PermanentWayItems");

      //! Check if there is a list as a child of an element
      bool HasPWItemList( const xercesc::DOMElement *parent ) const;

      //! Get the permanent way item list element from the children of an element
      xercesc::DOMElement* GetPWItemListElement( const xercesc::DOMElement *parent ) const;

      //! Read in the list of permanent way items
      std::vector<std::shared_ptr<Lineside::PWItemData>> Read( const xercesc::DOMElement *pwItemListElement ) const;
    };
  }
}
