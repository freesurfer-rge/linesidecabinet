#include <boost/test/unit_test.hpp>

#include "xmlutils.hpp"

#include "xml/configurationreader.hpp"

// ==============

const std::string configurationFile = "full-configuration-sample.xml";

// ==============

BOOST_AUTO_TEST_SUITE( ConfigurationReaderTests )

BOOST_AUTO_TEST_CASE( SmokeReader )
{
  Lineside::xml::ConfigurationReader reader;

  auto fullPath = GetPathToSampleXML( configurationFile );
  
  auto res = reader.Read( fullPath );

  BOOST_REQUIRE_EQUAL( res.pwItems.size(), 1 );
}

BOOST_AUTO_TEST_SUITE_END()
