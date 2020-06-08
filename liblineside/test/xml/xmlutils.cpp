#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "lineside/xml/utilities.hpp"

#include "xmlutils.hpp"

const std::string xmlSampleDir = "xmlsamples";

std::shared_ptr<xercesc::XercesDOMParser> GetParser() {
  auto parser = std::make_shared<xercesc::XercesDOMParser>();
  parser->setValidationScheme( xercesc::XercesDOMParser::Val_Never );
  parser->setDoNamespaces( false );
  parser->setDoSchema( false );
  parser->setLoadExternalDTD( false );

  return parser;
}


std::string GetPathToSampleXML( const std::string filename ) {
   // Figure out the location of the sample files
  boost::filesystem::path binaryPath(boost::unit_test::framework::master_test_suite().argv[0]);
  boost::filesystem::path p( boost::filesystem::absolute(binaryPath).parent_path() );
  p /= xmlSampleDir;
  p /= filename;

  BOOST_TEST_MESSAGE( boost::filesystem::absolute(binaryPath).parent_path() );
  BOOST_TEST_MESSAGE( p.c_str() );
  BOOST_REQUIRE( boost::filesystem::exists(p) );

  return p.native();
}

xercesc::DOMElement* GetRootElementOfFile(std::shared_ptr<xercesc::XercesDOMParser> parser,
					  const std::string filename) {
  /*
    Opens the designated file in the xmlSampleDir, and returns
    a pointer to the root element
  */


  // Load in the file
  parser->parse( GetPathToSampleXML( filename ).c_str() );

   // Get the root element
  auto TAG_Test = Lineside::xml::StrToXMLCh("Test");

  auto xmlDoc = parser->getDocument();
  auto rootElement = xmlDoc->getDocumentElement();
  BOOST_REQUIRE( rootElement );
  BOOST_REQUIRE( xercesc::XMLString::equals(rootElement->getTagName(), TAG_Test.get() ) );

  return rootElement;
}
