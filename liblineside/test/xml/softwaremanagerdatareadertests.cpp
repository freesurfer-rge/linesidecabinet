#include <boost/test/unit_test.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>

#include "xmlutils.hpp"

#include "lineside/xml/xercesguard.hpp"
#include "lineside/xml/utilities.hpp"

#include "lineside/xml/softwaremanagerdatareader.hpp"

// ==============

const std::string softwaremanagerdataFragment = "softwaremanagerdata-fragment.xml";

// ==============

BOOST_AUTO_TEST_SUITE( xml )

BOOST_AUTO_TEST_SUITE( SoftwareManagerDataReader )

BOOST_AUTO_TEST_CASE( SmokeReader )
{
  Lineside::xml::XercesGuard xg;
  auto parser = GetParser();

  auto rootElement = GetRootElementOfFile(parser, softwaremanagerdataFragment);
  BOOST_REQUIRE(rootElement);

  Lineside::xml::SoftwareManagerDataReader reader;
  BOOST_REQUIRE( reader.HasSoftwareManager(rootElement) );
  auto softwareManagerElement = reader.GetSoftwareManagerElement(rootElement);
  auto result = reader.Read(softwareManagerElement);
  BOOST_CHECK_EQUAL( result.rtcAddress, "addr" );
  BOOST_CHECK_EQUAL( result.rtcPort, 8080 );
  BOOST_REQUIRE_EQUAL( result.settings.size(), 1 );
  BOOST_CHECK_EQUAL( result.settings.at("a"), "b" );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
