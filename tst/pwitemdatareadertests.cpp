#include <boost/test/unit_test.hpp>

#include <memory>

#include <xercesc/parsers/XercesDOMParser.hpp>

#include "xmlutils.hpp"

#include "xml/xercesguard.hpp"
#include "xml/utilities.hpp"

#include "xml/servoturnoutmotordatareader.hpp"
#include "servoturnoutmotordata.hpp"

// ===========================

const std::string servoturnoutmotorFragment = "pwitem-servoturnoutmotor.xml";

// ===========================

BOOST_AUTO_TEST_SUITE( PWItemDataReader )

BOOST_AUTO_TEST_CASE( SmokeServoTurnoutMotorData )
{
  Lineside::xml::XercesGuard xg;
  auto parser = GetParser();

  auto rootElement = GetRootElementOfFile(parser, servoturnoutmotorFragment);
  BOOST_REQUIRE(rootElement);

  auto servoTurnoutMotorElement = Lineside::xml::GetSingleElementByName(rootElement, "ServoTurnoutMotor" );
  BOOST_REQUIRE( servoTurnoutMotorElement );

  Lineside::xml::ServoTurnoutMotorDataReader reader;

  auto result = reader.Read(servoTurnoutMotorElement);
  BOOST_REQUIRE(result);

  Lineside::ItemId expectedId;
  expectedId.Parse("00:fe:1a:af");
  BOOST_CHECK_EQUAL( result->id, expectedId );

  auto stmd = std::dynamic_pointer_cast<Lineside::ServoTurnoutMotorData>(result);
  BOOST_CHECK_EQUAL( stmd->straight, 130 );
  BOOST_CHECK_EQUAL( stmd->curved, 400 );
  BOOST_CHECK_EQUAL( stmd->pwmChannelRequest.controller, "sc01" );
  BOOST_CHECK_EQUAL( stmd->pwmChannelRequest.controllerData, "01" );
}

BOOST_AUTO_TEST_CASE( SmokeTrackCircuitMonitorData )
{
  BOOST_FAIL("Not yet implemented");
}

BOOST_AUTO_TEST_CASE( SmokeMultiaspectSignalHeadData )
{
  BOOST_FAIL("Not yet implemented");
}

BOOST_AUTO_TEST_SUITE_END()
