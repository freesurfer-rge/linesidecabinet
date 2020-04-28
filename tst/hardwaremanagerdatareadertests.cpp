#include <boost/test/unit_test.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>

#include "xmlutils.hpp"

#include "xml/xercesguard.hpp"
#include "xml/utilities.hpp"

#include "xml/hardwaremanagerdatareader.hpp"

// ==============

const std::string hardwaremanagerFragment = "hardwaremanager-fragment.xml";

// ==============

BOOST_AUTO_TEST_SUITE( HardwareManagerDataReader )

BOOST_AUTO_TEST_CASE( SmokeReader )
{
  Lineside::xml::XercesGuard xg;
  auto parser = GetParser();

  auto rootElement = GetRootElementOfFile(parser, hardwaremanagerFragment);
  BOOST_REQUIRE(rootElement);
  
  Lineside::xml::HardwareManagerDataReader reader;
  BOOST_REQUIRE( reader.HasHardwareManager(rootElement) );
  
  auto hardwaremanagerElement = reader.GetHardwareManagerElement(rootElement);

  auto result = reader.Read(hardwaremanagerElement);

  BOOST_REQUIRE_EQUAL( result.i2cDevices.size(), 1 );
  auto dev0 = result.i2cDevices.at(0);
  BOOST_CHECK_EQUAL( dev0.kind, "pca9685" );
  BOOST_CHECK_EQUAL( dev0.bus, 0 );
  BOOST_CHECK_EQUAL( dev0.address, 0xFF );
  BOOST_CHECK_EQUAL( dev0.name, "pwm0" );

  BOOST_REQUIRE_EQUAL( result.settings.size(), 1 );
  BOOST_CHECK_EQUAL( result.settings.at("some"), "value" );
}

BOOST_AUTO_TEST_SUITE_END()
