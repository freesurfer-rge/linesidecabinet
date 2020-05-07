#include <boost/test/unit_test.hpp>

#include "xmlutils.hpp"

#include "xml/configurationreader.hpp"

#include "trackcircuitmonitordata.hpp"

// ==============

const std::string configurationFile = "full-configuration-sample.xml";

// ==============

BOOST_AUTO_TEST_SUITE( ConfigurationReaderTests )

BOOST_AUTO_TEST_CASE( SmokeReader )
{
  Lineside::xml::ConfigurationReader reader;

  auto fullPath = GetPathToSampleXML( configurationFile );
  
  auto res = reader.Read( fullPath );

  // Check the software manager
  BOOST_CHECK_EQUAL( res.swManager.rtcAddress, "addr" );
  BOOST_CHECK_EQUAL( res.swManager.rtcPort, 8081 );
  BOOST_REQUIRE_EQUAL( res.swManager.settings.size(), 1 );
  BOOST_CHECK_EQUAL( res.swManager.settings.at("aKey"), "bValue" );

  // Check the hardware manager
  BOOST_REQUIRE_EQUAL( res.hwManager.i2cDevices.size(), 1 );
  auto dev0 = res.hwManager.i2cDevices.at(0);
  BOOST_CHECK_EQUAL( dev0.kind, "pca9685" );
  BOOST_CHECK_EQUAL( dev0.bus, 0 );
  BOOST_CHECK_EQUAL( dev0.address, 0x0F );
  BOOST_CHECK_EQUAL( dev0.name, "pwm0" );

  BOOST_REQUIRE_EQUAL( res.hwManager.settings.size(), 1 );
  BOOST_CHECK_EQUAL( res.hwManager.settings.at("some"), "thing" );

  // Check the list of PWItems
  BOOST_REQUIRE_EQUAL( res.pwItems.size(), 1 );
  auto item0 = res.pwItems.at(0);
  auto tcmd0 = std::dynamic_pointer_cast<Lineside::TrackCircuitMonitorData>(item0);
  BOOST_REQUIRE( tcmd0 );
  Lineside::ItemId expectedId;
  expectedId.Parse("10:fe:02:1a");
  BOOST_CHECK_EQUAL( tcmd0->id, expectedId );
  BOOST_CHECK_EQUAL( tcmd0->inputPinRequest.controller, "GPIO" );
  BOOST_CHECK_EQUAL( tcmd0->inputPinRequest.controllerData, "07" );
  BOOST_REQUIRE_EQUAL( tcmd0->inputPinRequest.settings.size(), 1 );
  BOOST_CHECK_EQUAL( tcmd0->inputPinRequest.settings.at("glitch"), "20000" );
}

BOOST_AUTO_TEST_SUITE_END()