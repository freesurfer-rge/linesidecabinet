#include <boost/test/unit_test.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>

#include "xmlutils.hpp"

#include "tendril/devices/device.hpp"
#include "tendril/devices/directdrivesn74x595data.hpp"

#include "lineside/xml/xercesguard.hpp"
#include "lineside/xml/utilities.hpp"

#include "lineside/xml/directdrivesn74x595datareader.hpp"

// ==============

const std::string dd595dataFragment = "device-directdrivesn74x595.xml";

// ==============

BOOST_AUTO_TEST_SUITE( xml )

BOOST_AUTO_TEST_SUITE( DirectDriveSN74x595DataReader )

BOOST_AUTO_TEST_CASE( SmokeReader )
{
  Lineside::xml::XercesGuard xg;
  auto parser = GetParser();

  auto rootElement = GetRootElementOfFile(parser, dd595dataFragment);
  BOOST_REQUIRE(rootElement);
  
  auto deviceElement = Lineside::xml::GetSingleElementByName(rootElement, "DirectDriveSN74x595" );
  BOOST_REQUIRE( deviceElement );
  
  Lineside::xml::DirectDriveSN74x595DataReader reader;
  BOOST_REQUIRE( !reader.CheckReadableElement(rootElement) );
  BOOST_REQUIRE( reader.CheckReadableElement(deviceElement) );

  auto result = reader.Read(deviceElement);
  BOOST_REQUIRE( result );
  auto dd595data = std::dynamic_pointer_cast<Tendril::Devices::DirectDriveSN74x595Data>(result);
  BOOST_REQUIRE(dd595data);
}


BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
