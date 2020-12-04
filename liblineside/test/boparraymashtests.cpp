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

BOOST_AUTO_TEST_CASE(TwoAspectOneFeather)
{
  const Lineside::ItemId id(15);
  
  // Create the target
  Lineside::BOPArrayMASH target(id);
  target.pins = std::make_unique<Tendril::Mocks::MockBOPArray>(3);
  const size_t redPin = 0;
  const size_t greenPin = 2;
  const size_t featherPin = 1;
  target.aspects[Lineside::SignalAspect::Red] = redPin;
  target.aspects[Lineside::SignalAspect::Green] = greenPin;
  target.feathers.push_back(featherPin);

  // Get access to the MockBOPArray
  auto mba = dynamic_cast<Tendril::Mocks::MockBOPArray*>(target.pins.get());
  BOOST_REQUIRE( mba );

  // Construction state
  BOOST_CHECK_EQUAL( target.getId(), id );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin), false );
  
  // Activate
  target.OnActivate();
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin), false );
  
  // Set to flashing green with the feather on
  target.SetState(Lineside::SignalState::Green,
		  Lineside::SignalFlash::Flashing,
		  1);
  auto sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin), true );

  // Call OnRun, green aspect should go out, but feather stays on
  sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin), true );

  // Call once more, and the green aspect comes back on
  sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin), true );

  // Now go for steady green without a feather
  target.SetState(Lineside::SignalState::Green,
		  Lineside::SignalFlash::Steady,
		  0);
  sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin), false );
  
  // Deactivate
  target.OnDeactivate();
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin), false );
}

BOOST_AUTO_TEST_CASE(TwoAspectTwoFeather)
{
  const Lineside::ItemId id(3253);

  // Create the target
  Lineside::BOPArrayMASH target(id);
  target.pins = std::make_unique<Tendril::Mocks::MockBOPArray>(4);
  const size_t redPin = 1;
  const size_t greenPin = 2;
  const size_t featherPin1 = 3;
  const size_t featherPin2 = 0;
  target.aspects[Lineside::SignalAspect::Red] = redPin;
  target.aspects[Lineside::SignalAspect::Green] = greenPin;
  target.feathers.push_back(featherPin1);
  target.feathers.push_back(featherPin2);

  // Get access to the MockBOPArray
  auto mba = dynamic_cast<Tendril::Mocks::MockBOPArray*>(target.pins.get());
  BOOST_REQUIRE( mba );

  // Construction state
  BOOST_CHECK_EQUAL( target.getId(), id );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin1), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin2), false );

  // Activate
  target.OnActivate();
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin1), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin2), false );

  // Set to green with one feather
  target.SetState(Lineside::SignalState::Green,
		  Lineside::SignalFlash::Steady,
		  1);
  auto sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin1), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin2), false );

  // And green with the other feather
  target.SetState(Lineside::SignalState::Green,
		  Lineside::SignalFlash::Steady,
		  2);
  sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin1), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin2), true );
  
  // Green without feathers
  target.SetState(Lineside::SignalState::Green,
		  Lineside::SignalFlash::Steady,
		  0);
  sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin1), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin2), false );

  // Deactivate
  target.OnDeactivate();
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin1), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin2), false );
}

BOOST_AUTO_TEST_CASE(ThreeAspect)
{
  const Lineside::ItemId id(116731);

  // Create the target
  Lineside::BOPArrayMASH target(id);
  target.pins = std::make_unique<Tendril::Mocks::MockBOPArray>(3);
  const size_t redPin = 1;
  const size_t yellowPin = 0;
  const size_t greenPin = 2;
  target.aspects[Lineside::SignalAspect::Red] = redPin;
  target.aspects[Lineside::SignalAspect::Yellow1] = yellowPin;
  target.aspects[Lineside::SignalAspect::Green] = greenPin;

  // Get access to the MockBOPArray
  auto mba = dynamic_cast<Tendril::Mocks::MockBOPArray*>(target.pins.get());
  BOOST_REQUIRE( mba );
  
  // Construction state
  BOOST_CHECK_EQUAL( target.getId(), id );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellowPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
  
  // Activate
  target.OnActivate();
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellowPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
  
  // Set to yellow and steady
  target.SetState(Lineside::SignalState::Yellow, Lineside::SignalFlash::Steady, 0);
  auto sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellowPin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
  
  // Deactivate
  target.OnDeactivate();
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellowPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
}

BOOST_AUTO_TEST_CASE(FourAspect)
{
  const Lineside::ItemId id(115);

  // Create the target
  Lineside::BOPArrayMASH target(id);
  target.pins = std::make_unique<Tendril::Mocks::MockBOPArray>(4);
  const size_t redPin = 1;
  const size_t yellow1Pin = 0;
  const size_t yellow2Pin = 3;
  const size_t greenPin = 2;
  target.aspects[Lineside::SignalAspect::Red] = redPin;
  target.aspects[Lineside::SignalAspect::Yellow1] = yellow1Pin;
  target.aspects[Lineside::SignalAspect::Yellow2] = yellow2Pin;
  target.aspects[Lineside::SignalAspect::Green] = greenPin;

  // Get access to the MockBOPArray
  auto mba = dynamic_cast<Tendril::Mocks::MockBOPArray*>(target.pins.get());
  BOOST_REQUIRE( mba );

  // Construction state
  BOOST_CHECK_EQUAL( target.getId(), id );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellow1Pin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellow2Pin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );

  // Activate
  target.OnActivate();
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellow1Pin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellow2Pin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );

  // Set to single yellow and steady
  target.SetState(Lineside::SignalState::Yellow, Lineside::SignalFlash::Steady, 0);
  auto sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellow1Pin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellow2Pin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
  
  // Set to double yellow and flashing
  target.SetState(Lineside::SignalState::DoubleYellow, Lineside::SignalFlash::Flashing, 0);
  sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellow1Pin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellow2Pin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );

  // Call OnRun() again, and check that everything is off
  sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellow1Pin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellow2Pin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );

  // One more time, and ensure both yellows are on
  sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellow1Pin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellow2Pin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );

  // Deactivate
  target.OnDeactivate();
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellow1Pin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellow2Pin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
}
  
BOOST_AUTO_TEST_SUITE_END()