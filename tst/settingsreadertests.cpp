#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <memory>

#include <xercesc/parsers/XercesDOMParser.hpp>

#include "xml/xercesguard.hpp"
#include "xml/utilities.hpp"
#include "xml/settingsreader.hpp"

// =================================

const std::string xmlSampleDir = "xmlsamples";

const std::string simpleSettingsFragment = "settings-fragment.xml";
const std::string simpleSettingsCommentFragment = "settings-comment-fragment.xml";

// =================================

std::shared_ptr<xercesc::XercesDOMParser> GetParser() {
  auto parser = std::make_shared<xercesc::XercesDOMParser>();
  parser->setValidationScheme( xercesc::XercesDOMParser::Val_Never );
  parser->setDoNamespaces( false );
  parser->setDoSchema( false );
  parser->setLoadExternalDTD( false );

  return parser;
}

xercesc::DOMElement* GetRootElementOfFile(std::shared_ptr<xercesc::XercesDOMParser> parser,
					  const std::string filename) {
  /*
    Opens the designated file in the xmlSampleDir, and returns
    a pointer to the root element
  */
  
  // Figure out the location of the sample files
  boost::filesystem::path binaryPath(boost::unit_test::framework::master_test_suite().argv[0]);
  boost::filesystem::path p( boost::filesystem::absolute(binaryPath).parent_path() );
  p /= xmlSampleDir;
  p /= filename;

  BOOST_TEST_MESSAGE( boost::filesystem::absolute(binaryPath).parent_path() );
  BOOST_TEST_MESSAGE( p.c_str() );
  BOOST_REQUIRE( boost::filesystem::exists(p) );

  // Load in the file
  parser->parse( p.c_str() );

   // Get the root element
  auto TAG_Test = Lineside::xml::StrToXMLCh("Test");

  auto xmlDoc = parser->getDocument();
  auto rootElement = xmlDoc->getDocumentElement();
  BOOST_REQUIRE( rootElement );
  BOOST_REQUIRE( xercesc::XMLString::equals(rootElement->getTagName(), TAG_Test.get() ) );

  return rootElement;
}

// =================================

BOOST_AUTO_TEST_SUITE( SettingsReader )

BOOST_AUTO_TEST_CASE( SmokeSimpleFragment )
{
  // Use guard to initialise library
  Lineside::xml::XercesGuard xg;

  // Configure the parser
  auto parser = GetParser();

  auto rootElement = GetRootElementOfFile(parser, simpleSettingsFragment);
  BOOST_REQUIRE(rootElement);

  Lineside::xml::SettingsReader reader;
  auto settingsElement = reader.GetSettingsElement(rootElement);
  auto result = reader.Read(settingsElement);
  BOOST_CHECK_EQUAL( result.size(), 2 );
  BOOST_CHECK_EQUAL( result.at("a"), "b" );
  BOOST_CHECK_EQUAL( result.at("1"), "2" );
}

BOOST_AUTO_TEST_CASE( SmokeSimpleFragmentWithComment )
{
  // Use guard to initialise library
  Lineside::xml::XercesGuard xg;

  // Configure the parser
  auto parser = GetParser();

  auto rootElement = GetRootElementOfFile(parser, simpleSettingsCommentFragment);
  BOOST_REQUIRE(rootElement);

  Lineside::xml::SettingsReader reader;
  auto settingsElement = reader.GetSettingsElement(rootElement);
  auto result = reader.Read(settingsElement);
  
  BOOST_CHECK_EQUAL( result.size(), 2 );
  BOOST_CHECK_EQUAL( result.at("c"), "d" );
  BOOST_CHECK_EQUAL( result.at("3"), "4" );
}

BOOST_AUTO_TEST_SUITE_END()
