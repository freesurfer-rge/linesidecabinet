#include <boost/test/unit_test.hpp>

#include <memory>

#include <xercesc/parsers/XercesDOMParser.hpp>

#include "xmlutils.hpp"

#include "lineside/xml/xercesguard.hpp"
#include "lineside/xml/utilities.hpp"

#include "lineside/xml/pwitemlistreader.hpp"

#include "lineside/servoturnoutmotordata.hpp"
#include "lineside/trackcircuitmonitordata.hpp"
#include "lineside/multiaspectsignalheaddata.hpp"

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
  BOOST_REQUIRE_EQUAL( pwItems.size(), 3 );

  auto tcmd = std::dynamic_pointer_cast<Lineside::TrackCircuitMonitorData>(pwItems.at(0));
  BOOST_REQUIRE( tcmd );
  Lineside::ItemId tcmId;
  tcmId.Parse("00:fe:00:1a");
  BOOST_CHECK_EQUAL( tcmd->id, tcmId );

  auto mashd = std::dynamic_pointer_cast<Lineside::MultiAspectSignalHeadData>(pwItems.at(1));
  BOOST_REQUIRE( mashd );
  Lineside::ItemId mashId;
  mashId.Parse("00:1f:2e:3d");
  BOOST_CHECK_EQUAL( mashd->id, mashId );

  auto stmd = std::dynamic_pointer_cast<Lineside::ServoTurnoutMotorData>(pwItems.at(2));
  BOOST_REQUIRE( stmd );
  Lineside::ItemId stmId;
  stmId.Parse("00:0e:2a:5f");
  BOOST_CHECK_EQUAL( stmd->id, stmId );
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
  Lineside::ItemId id;
  id.Parse("00:fe:00:1a");
  expectedIds.push_back(id);
  id.Parse("00:fe:00:00");
  expectedIds.push_back(id);
  for( size_t i=0; i<pwItems.size(); i++ ) {
    auto tcmd = std::dynamic_pointer_cast<Lineside::TrackCircuitMonitorData>(pwItems.at(i));
    BOOST_REQUIRE( tcmd );
    BOOST_CHECK_EQUAL( tcmd->id, expectedIds.at(i) );
  }
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()