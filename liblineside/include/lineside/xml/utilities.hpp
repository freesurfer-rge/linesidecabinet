#pragma once

#include <memory>
#include <string>

#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOMElement.hpp>

#include "lineside/xml/xercesstringdeleter.hpp"

namespace Lineside {
  namespace xml {
    //! Convert a std::string to a Xerces string
    XercesPtr<XMLCh> StrToXMLCh( const std::string& str );

    //! Convert a Xerces string back to a std::string
    std::string XMLChToStr( const XMLCh* xmlChars );
    
    bool IsElementNode( const xercesc::DOMNode* node );
    bool HasChildElement( const xercesc::DOMElement* parent,
			  const std::string name );
    
    xercesc::DOMElement* GetSingleElementByName( const xercesc::DOMElement* parent,
						 const std::string name );

    std::string GetAttributeByName( const xercesc::DOMElement* element,
				    const std::string name );
  }
}
