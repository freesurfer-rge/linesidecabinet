#include <boost/test/unit_test.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>

#include "xmlutils.hpp"

#include "xml/xercesguard.hpp"
#include "xml/utilities.hpp"

#include "xml/softwaremanagerdatareader.hpp"

// ==============

const std::string softwaremanagerdataFragment = "softwaremanagerdata-fragment.xml";

// ==============

BOOST_AUTO_TEST_SUITE( SoftwareManagerDataReader )

BOOST_AUTO_TEST_CASE( SmokeReader )
{
  Lineside::xml::XercesGuard xg;
  auto parser = GetParser();

  auto rootElement = GetRootElementOfFile(parser, softwaremanagerdataFragment);
  BOOST_REQUIRE(rootElement);
}

BOOST_AUTO_TEST_SUITE_END()
