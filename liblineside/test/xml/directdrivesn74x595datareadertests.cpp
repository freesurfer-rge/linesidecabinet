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

  BOOST_CHECK_EQUAL( dd595data->name, "myChip" );
  
  BOOST_CHECK_EQUAL( dd595data->clockPin.providerName, "GPIO1" );
  BOOST_CHECK_EQUAL( dd595data->clockPin.idOnProvider, "01" );
  BOOST_CHECK_EQUAL( dd595data->clockPin.settings.size(), 0 );
  
  BOOST_CHECK_EQUAL( dd595data->latchPin.providerName, "GPIO2" );
  BOOST_CHECK_EQUAL( dd595data->latchPin.idOnProvider, "02" );
  BOOST_CHECK_EQUAL( dd595data->latchPin.settings.size(), 0 );
  
  BOOST_CHECK_EQUAL( dd595data->dataPin.providerName, "GPIO3" );
  BOOST_CHECK_EQUAL( dd595data->dataPin.idOnProvider, "03" );
  BOOST_CHECK_EQUAL( dd595data->dataPin.settings.size(), 0 );
  
  BOOST_CHECK_EQUAL( dd595data->clearPin.providerName, "GPIO4" );
  BOOST_CHECK_EQUAL( dd595data->clearPin.idOnProvider, "04" );
  BOOST_CHECK_EQUAL( dd595data->clearPin.settings.size(), 0 );
  
  BOOST_CHECK_EQUAL( dd595data->enablePin.providerName, "GPIO5" );
  BOOST_CHECK_EQUAL( dd595data->enablePin.idOnProvider, "05" );
  BOOST_CHECK_EQUAL( dd595data->enablePin.settings.size(), 0 );

  BOOST_REQUIRE_EQUAL( dd595data->settings.size(), 1 );
  BOOST_CHECK_EQUAL( dd595data->settings.at("chainLength"), "2" );
}


BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
