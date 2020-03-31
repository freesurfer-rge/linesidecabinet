#pragma once

#include <vector>
#include <memory>
#include <string>

#include <xercesc/dom/DOMElement.hpp>

#include "pwitemdata.hpp"

namespace Lineside {
  namespace xml {
    class PWItemListReader {
    public:
      const std::string ListElement = std::string("PermanentWayItems");
      
      bool HasPWItemList( const xercesc::DOMElement *parent ) const;

      xercesc::DOMElement* GetPWItemListElement( const xercesc::DOMElement *parent ) const;

      std::vector<std::shared_ptr<Lineside::PWItemData>> Read( const xercesc::DOMElement *pwItemListElement ) const;
    };
  }
}
