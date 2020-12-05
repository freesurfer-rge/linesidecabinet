#include <boost/test/unit_test.hpp>

#include <memory>

#include <xercesc/parsers/XercesDOMParser.hpp>

#include "xmlutils.hpp"

#include "lineside/xml/xercesguard.hpp"
#include "lineside/xml/utilities.hpp"

#include "lineside/xml/pwitemlistreader.hpp"

#include "lineside/servoturnoutmotordata.hpp"
#include "lineside/trackcircuitmonitordata.hpp"
#include "lineside/directdrivemashdata.hpp"
#include "lineside/boparraymashdata.hpp"

// ====================

const std::string pwitemlistFragment = "pwitemlist.xml";
const std::string pwitemlistTwoTCMFragment = "pwitemlist-two-tcm.xml";

// ====================

BOOST_AUTO_TEST_SUITE( xml )

BOOST_AUTO_TEST_SUITE( PWItemListReader )

BOOST_AUTO_TEST_CASE( SmokePWItemListReader )
{
  Lineside::xml::XercesGuard xg;
  auto parser = GetParser();

  auto rootElement = GetRootElementOfFile(parser, pwitemlistFragment);
  BOOST_REQUIRE(rootElement);

  Lineside::xml::PWItemListReader reader;
  auto listElement = reader.GetPWItemListElement(rootElement);
  BOOST_REQUIRE(listElement);

  std::vector<std::shared_ptr<Lineside::PWItemData>> pwItems = reader.Read(listElement);
  BOOST_REQUIRE_EQUAL( pwItems.size(), 4 );

  auto tcmd = std::dynamic_pointer_cast<Lineside::TrackCircuitMonitorData>(pwItems.at(0));
  BOOST_REQUIRE( tcmd );
  auto tcmId = Lineside::Parse<Lineside::ItemId>("00:fe:00:1a");
  BOOST_CHECK_EQUAL( tcmd->id, tcmId );

  auto mashd = std::dynamic_pointer_cast<Lineside::DirectDriveMASHData>(pwItems.at(1));
  BOOST_REQUIRE( mashd );
  auto mashId = Lineside::Parse<Lineside::ItemId>("00:1f:2e:3d");
  BOOST_CHECK_EQUAL( mashd->id, mashId );

  auto stmd = std::dynamic_pointer_cast<Lineside::ServoTurnoutMotorData>(pwItems.at(2));
  BOOST_REQUIRE( stmd );
  auto stmId = Lineside::Parse<Lineside::ItemId>("00:0e:2a:5f");
  BOOST_CHECK_EQUAL( stmd->id, stmId );

  auto boparraymashd = std::dynamic_pointer_cast<Lineside::BOPArrayMASHData>(pwItems.at(3));
  BOOST_REQUIRE( boparraymashd );
  auto boparraymashId = Lineside::Parse<Lineside::ItemId>("2b:3c:00:1a");
  BOOST_CHECK_EQUAL( boparraymashd->id, boparraymashId );
}

BOOST_AUTO_TEST_CASE( TwoTrackCircuitMonitors )
{
  Lineside::xml::XercesGuard xg;
  auto parser = GetParser();

  auto rootElement = GetRootElementOfFile(parser, pwitemlistTwoTCMFragment);
  BOOST_REQUIRE(rootElement);

  Lineside::xml::PWItemListReader reader;
  auto listElement = reader.GetPWItemListElement(rootElement);
  BOOST_REQUIRE(listElement);

  std::vector<std::shared_ptr<Lineside::PWItemData>> pwItems = reader.Read(listElement);
  BOOST_REQUIRE_EQUAL( pwItems.size(), 2 );

  std::vector<Lineside::ItemId> expectedIds;
  expectedIds.push_back(Lineside::Parse<Lineside::ItemId>("00:fe:00:1a"));
  expectedIds.push_back(Lineside::Parse<Lineside::ItemId>("00:fe:00:00"));
  std::vector<Lineside::TrackCircuitSensor> expectedSensors;
  expectedSensors.push_back(Lineside::TrackCircuitSensor::OccupiedIsLow);
  expectedSensors.push_back(Lineside::TrackCircuitSensor::OccupiedIsHigh);
  for( size_t i=0; i<pwItems.size(); i++ ) {
    auto tcmd = std::dynamic_pointer_cast<Lineside::TrackCircuitMonitorData>(pwItems.at(i));
    BOOST_REQUIRE( tcmd );
    BOOST_CHECK_EQUAL( tcmd->id, expectedIds.at(i) );
    BOOST_CHECK_EQUAL( tcmd->sensor, expectedSensors.at(i) );
  }
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
