#include <boost/test/unit_test.hpp>

#include "tendril/mocks/mockboparray.hpp"

#include "lineside/boparraymash.hpp"

// =======================================

BOOST_AUTO_TEST_SUITE(BOPArrayMASH)

BOOST_AUTO_TEST_CASE(TwoAspect)
{
  const Lineside::ItemId id(16);

  // Create the target
  Lineside::BOPArrayMASH target(id);
  target.pins = std::make_unique<Tendril::Mocks::MockBOPArray>(2);
  const size_t redPin = 0;
  const size_t greenPin = 1;
  target.aspects[Lineside::SignalAspect::Red] = redPin;
  target.aspects[Lineside::SignalAspect::Green] = greenPin;

  // Get access to the MockBOPArray
  auto mba = dynamic_cast<Tendril::Mocks::MockBOPArray*>(target.pins.get());
  BOOST_REQUIRE( mba );

  // Construction state
  BOOST_CHECK_EQUAL( target.getId(), id );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
  
  // Activate
  target.OnActivate();
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
  
  // Set to green
  target.SetState(Lineside::SignalState::Green,
		  Lineside::SignalFlash::Steady,
		  0);
  auto sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), true );

  // Call OnRun again, but we didn't set it flashing
  sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), true );

  // Set to flashing red
  target.SetState(Lineside::SignalState::Red,
		  Lineside::SignalFlash::Flashing,
		  0);
  sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );

  // Call OnRun again, and this time we are flashing
  sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );

  // And one more time, since the aspect should be back on
  sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );

  // Deactivate
  target.OnDeactivate();
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
}

BOOST_AUTO_TEST_SUITE_END()
