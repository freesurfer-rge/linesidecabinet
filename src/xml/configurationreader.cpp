#include <stdexcept>

#include <xercesc/parsers/XercesDOMParser.hpp>

#include "lineside/xml/utilities.hpp"

#include "lineside/xml/softwaremanagerdatareader.hpp"
#include "lineside/xml/hardwaremanagerdatareader.hpp"
#include "lineside/xml/pwitemlistreader.hpp"

#include "lineside/xml/configurationreader.hpp"

namespace Lineside {
  namespace xml {
    ConfigurationData ConfigurationReader::Read( const std::string filePath ) const {
      if( filePath.empty() ) {
	throw std::logic_error("Empty filePath");
      }

      // Set up the parser
      xercesc::XercesDOMParser parser;
      parser.setValidationScheme( xercesc::XercesDOMParser::Val_Never );
      parser.setDoNamespaces( false );
      parser.setDoSchema( false );
      parser.setLoadExternalDTD( false );

      // Read the file into Xerces
      parser.parse( filePath.c_str() );

      // Get the root element
      auto xmlDoc = parser.getDocument();
      auto rootElement = xmlDoc->getDocumentElement();
      if( !rootElement ) {
	throw std::logic_error("Could not get root element of document");
      }

      if( !xercesc::XMLString::equals(rootElement->getTagName(),
				      Lineside::xml::StrToXMLCh(this->LinesideCabinetElement).get() ) ) {
	throw std::logic_error("Bad name for root element");
      }

      SoftwareManagerDataReader swReader;
      HardwareManagerDataReader hwReader;
      PWItemListReader pwItemReader;
      
      ConfigurationData result;

      result.swManager = swReader.Read( swReader.GetSoftwareManagerElement( rootElement ) );
      result.hwManager = hwReader.Read( hwReader.GetHardwareManagerElement( rootElement ) );
      result.pwItems = pwItemReader.Read( pwItemReader.GetPWItemListElement( rootElement ) );
      
      return result;
    }
  }
}
