#include <boost/test/unit_test.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>

#include "xmlutils.hpp"

#include "lineside/xml/xercesguard.hpp"
#include "lineside/xml/utilities.hpp"

#include "lineside/xml/i2cdevicelistreader.hpp"

// ==============

const std::string i2cdevicelistFragment = "i2cdevicelist-fragment.xml";

// ==============

BOOST_AUTO_TEST_SUITE( xml )

BOOST_AUTO_TEST_SUITE( I2CDeviceListReader )

BOOST_AUTO_TEST_CASE( SmokeReader )
{
  Lineside::xml::XercesGuard xg;
  auto parser = GetParser();

  auto rootElement = GetRootElementOfFile(parser, i2cdevicelistFragment);
  BOOST_REQUIRE(rootElement);

  Lineside::xml::I2CDeviceListReader reader;
  BOOST_REQUIRE( reader.HasI2CDeviceList(rootElement) );
  auto i2cDeviceListElement = reader.GetI2CDeviceListElement(rootElement);
  auto result = reader.Read(i2cDeviceListElement);
  BOOST_REQUIRE_EQUAL( result.size(), 2 );

  auto dev0 = result.at(0);
  BOOST_CHECK_EQUAL( dev0.kind, "devKind" );
  BOOST_CHECK_EQUAL( dev0.bus, 1 );
  BOOST_CHECK_EQUAL( dev0.address, 0x10 );
  BOOST_CHECK_EQUAL( dev0.name, "dev1" );
  BOOST_REQUIRE_EQUAL( dev0.settings.size(), 2 );
  BOOST_CHECK_EQUAL( dev0.settings.at("A"), "B" );
  BOOST_CHECK_EQUAL( dev0.settings.at("1"), "2" );

  auto dev1 = result.at(1);
  BOOST_CHECK_EQUAL( dev1.kind, "tstKind" );
  BOOST_CHECK_EQUAL( dev1.bus, 2 );
  BOOST_CHECK_EQUAL( dev1.address, 0x08 );
  BOOST_CHECK_EQUAL( dev1.name, "dev2" );
  BOOST_REQUIRE_EQUAL( dev1.settings.size(), 0 );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
