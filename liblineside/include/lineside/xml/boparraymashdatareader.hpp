#pragma once

#include "lineside/xml/pwitemdatareader.hpp"

namespace Lineside {
  namespace xml {
    class BOPArrayMASHDataReader : public PWItemDataReader {
    public:
      virtual bool MatchingElement( const xercesc::DOMElement *element ) const override;
      
      virtual std::shared_ptr<Lineside::PWItemData> Read( const xercesc::DOMElement *pwItemElement ) const override;

    };
  }
}
