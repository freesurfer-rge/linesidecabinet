#include <sstream>

#include <xercesc/dom/DOMNodeList.hpp>

#include "lineside/xml/utilities.hpp"

namespace Lineside {
  namespace xml {
    XercesPtr<XMLCh> StrToXMLCh( const std::string& str ) {
      XMLCh* tc = xercesc::XMLString::transcode(str.c_str());
      return UniqueXercesPtr(tc);
    }

    std::string XMLChToStr( const XMLCh* xmlChars ) {
      auto chars = UniqueXercesPtr(xercesc::XMLString::transcode(xmlChars));
      return std::string(chars.get());
    }

    bool IsElementNode( const xercesc::DOMNode* node ) {
      return (node->getNodeType()) &&
	(node->getNodeType() == xercesc::DOMNode::ELEMENT_NODE );
    }

    bool HasChildElement( const xercesc::DOMElement* parent,
			  const std::string name ) {
      auto TAG_Name = StrToXMLCh(name);
      
      auto elementList = parent->getElementsByTagName( TAG_Name.get() );
      if( elementList == nullptr ) {
	std::stringstream msg;
	msg << "Failed getElementsByTagName call for " << name;
	throw std::runtime_error(msg.str());
      }
      
      if( elementList->getLength() > 0 ) {
	return true;
      }

      return false;
    }

    xercesc::DOMElement* GetSingleElementByName( const xercesc::DOMElement* parent,
						 const std::string name ) {
      auto TAG_Name = StrToXMLCh(name);

      int resultCount = 0;
      xercesc::DOMElement* result = nullptr;
      
      // We only want the direct children, so can't use getElementsByTagName
      auto childList = parent->getChildNodes();
      for( XMLSize_t i=0; i<childList->getLength(); i++ ) {
	auto child = childList->item(i);
	if( IsElementNode(child) ) {
	  auto element = dynamic_cast<xercesc::DOMElement*>(child);

	  if( xercesc::XMLString::equals( element->getTagName(), TAG_Name.get() )) {
	    resultCount++;
	    result = element;
	  }
	}
      }
      
      if( resultCount != 1 ) {
	std::stringstream msg;
	msg << "Did not find exactly one child element " << name
	    << " in element " << XMLChToStr(parent->getTagName());
	throw std::runtime_error(msg.str());
      }
      
      return result;
    }

    std::string GetAttributeByName( const xercesc::DOMElement* element,
				    const std::string name ) {
      auto tcName = StrToXMLCh(name);
      auto attr = element->getAttribute(tcName.get());
      return XMLChToStr(attr);
    }
  }
}
