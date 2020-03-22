#pragma once

#include <memory>
#include <xercesc/dom/DOMElement.hpp>
#include "pwitemdata.hpp"

namespace Lineside {
  namespace xml {
    class PWItemDataReader {
    public:
      Lineside::ItemId ReadIdAttribute( const xercesc::DOMElement *pwItemElement ) const;
      
      virtual std::shared_ptr<Lineside::PWItemData> Read( const xercesc::DOMElement *pwItemElement ) const = 0;

      virtual ~PWItemDataReader() {}
    };
  }
}
