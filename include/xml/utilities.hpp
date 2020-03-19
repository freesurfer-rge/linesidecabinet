#pragma once

#include <memory>
#include <string>

#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOMElement.hpp>

#include "xml/xercesstringdeleter.hpp"

namespace Lineside {
  namespace xml {
    std::unique_ptr<XMLCh,xercesstringdeleter> StrToXMLCh( const std::string& str );
    std::string XMLChToStr( const XMLCh* xmlChars );
    
    bool IsElementNode( const xercesc::DOMNode* node );
    
    xercesc::DOMElement* GetSingleElementByName( const xercesc::DOMElement* parent,
						 const std::string name);
    
    std::string GetAttributeByName( const xercesc::DOMElement* element,
				    const std::string name );
  }
}
