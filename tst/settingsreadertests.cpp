#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <memory>

#include <xercesc/parsers/XercesDOMParser.hpp>

#include "xml/xercesguard.hpp"
#include "xml/settingsreader.hpp"

// =================================

const std::string xmlSampleDir = "xmlsamples";

const std::string simpleSettingsFragment = "settings-fragment.xml";

// =================================

BOOST_AUTO_TEST_SUITE( SettingsReader )

BOOST_AUTO_TEST_CASE( SmokeSimpleFragment )
{
  // Use guard to initialise library
  Lineside::xml::XercesGuard xg;

  // Configure the parser
  auto parser = std::unique_ptr<xercesc::XercesDOMParser>(new xercesc::XercesDOMParser);
  parser->setValidationScheme( xercesc::XercesDOMParser::Val_Never );
  parser->setDoNamespaces( false );
  parser->setDoSchema( false );
  parser->setLoadExternalDTD( false );

  // Figure out the location of the sample files
  boost::filesystem::path binaryPath(boost::unit_test::framework::master_test_suite().argv[0]);
  boost::filesystem::path p( boost::filesystem::absolute(binaryPath).parent_path() );
  p /= xmlSampleDir;
  p /= simpleSettingsFragment;

  BOOST_TEST_MESSAGE( boost::filesystem::absolute(binaryPath).parent_path() );
  BOOST_TEST_MESSAGE( p.c_str() );
  BOOST_REQUIRE( boost::filesystem::exists(p) );
}

BOOST_AUTO_TEST_SUITE_END()
