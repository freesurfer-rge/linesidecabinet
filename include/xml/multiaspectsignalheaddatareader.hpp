#pragma once

#include "xml/pwitemdatareader.hpp"

namespace Lineside {
  namespace xml {
    class MultiAspectSignalHeadDataReader : public PWItemDataReader {
    public:
      virtual std::shared_ptr<Lineside::PWItemData> Read( const xercesc::DOMElement *pwItemElement ) const override;

    };
  }
}
