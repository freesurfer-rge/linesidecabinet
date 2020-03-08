#include <boost/test/unit_test.hpp>

#include "trackcircuitmonitordata.hpp"
#include "trackcircuitmonitor.hpp"

#include "mockmanagerfixture.hpp"

BOOST_FIXTURE_TEST_SUITE(TrackCircuitMonitor, MockManagerFixture)

BOOST_AUTO_TEST_CASE(Construct)
{
  const Lineside::ItemId id(10);
  const std::string controller = "BIP";
  const std::string controllerData = "07";

  Lineside::TrackCircuitMonitorData tcmd;
  tcmd.id = id;
  tcmd.inputPinRequest.controller = controller;
  tcmd.inputPinRequest.controllerData = controllerData;

  auto pwItem = tcmd.Construct(this->hwManager, this->swManager);
  BOOST_REQUIRE( pwItem );
  BOOST_CHECK_EQUAL( pwItem->getId(), id );
  auto tcm = std::dynamic_pointer_cast<Lineside::TrackCircuitMonitor>(pwItem);
  BOOST_REQUIRE( tcm );
  BOOST_REQUIRE_EQUAL( tcm.use_count(), 2 ); // pwItem and tcm itself
}

BOOST_AUTO_TEST_SUITE_END()
