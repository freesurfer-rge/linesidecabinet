#pragma once

#include <memory>
#include <string>

#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOMElement.hpp>

#include "xml/xercesstringdeleter.hpp"

namespace Lineside {
  namespace xml {
    std::unique_ptr<XMLCh,xercesstringdeleter> StrToXMLCh( const std::string& str );

    xercesc::DOMElement* GetSingleElementByName( const xercesc::DOMElement* parent, const std::string name );
  }
}
