#include <boost/test/unit_test.hpp>

#include <memory>

#include <xercesc/parsers/XercesDOMParser.hpp>

#include "xmlutils.hpp"

#include "xml/xercesguard.hpp"
#include "xml/utilities.hpp"

#include "xml/servoturnoutmotordatareader.hpp"
#include "xml/trackcircuitmonitordatareader.hpp"
#include "xml/multiaspectsignalheaddatareader.hpp"

#include "servoturnoutmotordata.hpp"
#include "trackcircuitmonitordata.hpp"
#include "multiaspectsignalheaddata.hpp"

// ===========================

const std::string servoturnoutmotorFragment = "pwitem-servoturnoutmotor.xml";
const std::string trackcircuitmonitorFragment = "pwitem-trackcircuitmonitor.xml";
const std::string multiaspectsignalheadFragment = "pwitem-multiaspectsignalhead.xml";

// ===========================

BOOST_AUTO_TEST_SUITE( xml )

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

  BOOST_CHECK( reader.MatchingElement(servoTurnoutMotorElement) );
  
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
  BOOST_CHECK_EQUAL( stmd->pwmChannelRequest.settings.size(), 0 );
}

BOOST_AUTO_TEST_CASE( SmokeTrackCircuitMonitorData )
{
  Lineside::xml::XercesGuard xg;
  auto parser = GetParser();

  auto rootElement = GetRootElementOfFile(parser, trackcircuitmonitorFragment);
  BOOST_REQUIRE(rootElement);

  auto tcmElement = Lineside::xml::GetSingleElementByName(rootElement, "TrackCircuitMonitor");
  BOOST_REQUIRE( tcmElement );

  Lineside::xml::TrackCircuitMonitorDataReader reader;

  BOOST_CHECK( reader.MatchingElement(tcmElement) );
  
  auto result = reader.Read(tcmElement);
  BOOST_REQUIRE(result);

  Lineside::ItemId expectedId;
  expectedId.Parse("00:ff:00:aa");
  BOOST_CHECK_EQUAL( result->id, expectedId );

  auto tcmd = std::dynamic_pointer_cast<Lineside::TrackCircuitMonitorData>(result);
  BOOST_CHECK_EQUAL( tcmd->inputPinRequest.controller, "GPIO" );
  BOOST_CHECK_EQUAL( tcmd->inputPinRequest.controllerData, "07" );
  BOOST_CHECK_EQUAL( tcmd->inputPinRequest.settings.size(), 1 );
  BOOST_CHECK_EQUAL( tcmd->inputPinRequest.settings.at("glitch"), "10000" );
}

BOOST_AUTO_TEST_CASE( SmokeMultiaspectSignalHeadData )
{
  Lineside::xml::XercesGuard xg;
  auto parser = GetParser();

  auto rootElement = GetRootElementOfFile(parser, multiaspectsignalheadFragment);
  BOOST_REQUIRE(rootElement);

  auto mashElement = Lineside::xml::GetSingleElementByName(rootElement, "MultiAspectSignalHead" );
  BOOST_REQUIRE( mashElement );

  Lineside::xml::MultiAspectSignalHeadDataReader reader;
  
  BOOST_CHECK( reader.MatchingElement(mashElement) );

  auto result = reader.Read(mashElement);
  BOOST_REQUIRE(result);

  Lineside::ItemId expectedId;
  expectedId.Parse("00:1a:2b:3c");
  BOOST_CHECK_EQUAL( result->id, expectedId );

  auto mashd = std::dynamic_pointer_cast<Lineside::MultiAspectSignalHeadData>(result);
  BOOST_REQUIRE(mashd);
  
  BOOST_CHECK_EQUAL( mashd->aspectRequests.size(), 3 );
  auto redRequest = mashd->aspectRequests.at(Lineside::SignalAspect::Red);
  BOOST_CHECK_EQUAL( redRequest.controller, "GPIO" );
  BOOST_CHECK_EQUAL( redRequest.controllerData, "03" );
  BOOST_CHECK_EQUAL( redRequest.settings.size(), 0 );
  auto yellow1Request = mashd->aspectRequests.at(Lineside::SignalAspect::Yellow1);
  BOOST_CHECK_EQUAL( yellow1Request.controller, "GPIO1" );
  BOOST_CHECK_EQUAL( yellow1Request.controllerData, "04" );
  BOOST_CHECK_EQUAL( yellow1Request.settings.size(), 0 );
  auto greenRequest = mashd->aspectRequests.at(Lineside::SignalAspect::Green);
  BOOST_CHECK_EQUAL( greenRequest.controller, "GPIO3" );
  BOOST_CHECK_EQUAL( greenRequest.controllerData, "06" );
  BOOST_CHECK_EQUAL( greenRequest.settings.size(), 0 );

  BOOST_CHECK_EQUAL( mashd->featherRequests.size(), 1 );
  auto f1Request = mashd->featherRequests.at(1);
  BOOST_CHECK_EQUAL( f1Request.controller, "GPIO2" );
  BOOST_CHECK_EQUAL( f1Request.controllerData, "08" );
  BOOST_CHECK_EQUAL( f1Request.settings.size(), 0 );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
