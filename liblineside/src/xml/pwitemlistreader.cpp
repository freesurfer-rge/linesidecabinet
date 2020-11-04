#include <xercesc/dom/DOMNodeList.hpp>

#include "lineside/xml/utilities.hpp"

#include "lineside/xml/servoturnoutmotordatareader.hpp"
#include "lineside/xml/trackcircuitmonitordatareader.hpp"
#include "lineside/xml/directdrivemashdatareader.hpp"

#include "lineside/xml/pwitemlistreader.hpp"

namespace Lineside {
  namespace xml {
    bool PWItemListReader::HasPWItemList( const xercesc::DOMElement *parent ) const {
      if( !parent ) {
	throw std::logic_error("Bad parent");
      }

      return HasChildElement( parent, PWItemListReader::ListElement );
    }
    
    xercesc::DOMElement* PWItemListReader::GetPWItemListElement( const xercesc::DOMElement *parent ) const {
      if( !parent ) {
	throw std::logic_error("Bad parent");
      }

      auto pwItemListElement = Lineside::xml::GetSingleElementByName(parent, PWItemListReader::ListElement );
      if( !pwItemListElement ) {
	throw std::logic_error("Could not get element for PWItem list");
      }
      return pwItemListElement;
    }
    
    std::vector<std::shared_ptr<Lineside::PWItemData>> PWItemListReader::Read( const xercesc::DOMElement *pwItemListElement ) const {
      if( !pwItemListElement ) {
	throw std::logic_error("Bad pwItemListElement");
      }
      auto result = std::vector<std::shared_ptr<Lineside::PWItemData>>();

      auto children = pwItemListElement->getChildNodes();

      // Construct the set of readers
      std::vector<std::unique_ptr<PWItemDataReader>> readers;
      readers.push_back(std::unique_ptr<PWItemDataReader>(new ServoTurnoutMotorDataReader));
      readers.push_back(std::unique_ptr<PWItemDataReader>(new DirectDriveMASHDataReader));
      readers.push_back(std::unique_ptr<PWItemDataReader>(new TrackCircuitMonitorDataReader));

      // Loop over the child nodes
      for( XMLSize_t i=0; i<children->getLength(); i++ ) {
	auto child = children->item(i);
	if( IsElementNode(child) ) {
	  auto element = dynamic_cast<xercesc::DOMElement*>(child);

	  bool hadMatch = false;
	  // See if a reader matches
	  for( auto r=readers.begin(); r!=readers.end(); ++r ) {
	    if( (*r)->MatchingElement(element) ) {
	      if( hadMatch ) {
		throw std::logic_error("Multiple matches for readers");
	      }
	      hadMatch = true;
	      result.push_back( (*r)->Read(element) );
	    }
	  }
	}
      }
      
      return result;
    }
  }
}
