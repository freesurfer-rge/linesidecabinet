#include <set>

#include <boost/test/unit_test.hpp>

#include "tendril/mocks/mockbop.hpp"

// #include "lineside/directdrivemashdata.hpp"
#include "lineside/directdrivemash.hpp"


#include "exceptionmessagecheck.hpp"

// =====================================

BOOST_AUTO_TEST_SUITE(DirectDriveMASH)

BOOST_AUTO_TEST_CASE(TwoAspect)
{
  const Lineside::ItemId id(11);

  // Create the target
  Lineside::DirectDriveMASH target(id);
  target.red = std::make_unique<Tendril::Mocks::MockBOP>();
  target.green = std::make_unique<Tendril::Mocks::MockBOP>();

  // Copy the pointers so that we can see the state 
  auto red = dynamic_cast<Tendril::Mocks::MockBOP*>(target.red.get());
  auto green = dynamic_cast<Tendril::Mocks::MockBOP*>(target.green.get());
  BOOST_REQUIRE( red );
  BOOST_REQUIRE( green );

  // Construction state
  BOOST_CHECK_EQUAL( target.getId(), id );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, false );

  // Activate
  target.OnActivate();
  BOOST_CHECK_EQUAL( red->lastLevel, true );
  BOOST_CHECK_EQUAL( green->lastLevel, false );
  
  // Set to green
  target.SetState(Lineside::SignalState::Green, Lineside::SignalFlash::Steady, 0);
  auto sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, true );

  // Call OnRun again, but we didn't set it flashing
  sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, true );

  // Set to flashing red
  target.SetState(Lineside::SignalState::Red, Lineside::SignalFlash::Flashing, 0);
  sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, true );
  BOOST_CHECK_EQUAL( green->lastLevel, false );

  // Call OnRun again, and this time we are flashing
  sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, false );

  // And one more time, since the aspect should be back on
  sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, true );
  BOOST_CHECK_EQUAL( green->lastLevel, false );

  // Deactivate
  target.OnDeactivate();
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, false );
}

BOOST_AUTO_TEST_CASE(TwoAspectOneFeather)
{
  const Lineside::ItemId id(15);

  // Create the target
  Lineside::DirectDriveMASH target(id);
  target.red = std::make_unique<Tendril::Mocks::MockBOP>();
  target.green = std::make_unique<Tendril::Mocks::MockBOP>();
  target.feathers.push_back(std::make_unique<Tendril::Mocks::MockBOP>());

  // Copy the pointers so that we can see the state 
  auto red = dynamic_cast<Tendril::Mocks::MockBOP*>(target.red.get());
  auto green = dynamic_cast<Tendril::Mocks::MockBOP*>(target.green.get());
  auto feather = dynamic_cast<Tendril::Mocks::MockBOP*>(target.feathers.at(0).get());
  BOOST_REQUIRE( red );
  BOOST_REQUIRE( green );
  BOOST_REQUIRE( feather );

  // Construction state
  BOOST_CHECK_EQUAL( target.getId(), id );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, false );
  BOOST_CHECK_EQUAL( feather->lastLevel, false );

  // Activate
  target.OnActivate();
  BOOST_CHECK_EQUAL( red->lastLevel, true );
  BOOST_CHECK_EQUAL( green->lastLevel, false );
  BOOST_CHECK_EQUAL( feather->lastLevel, false );

  // Set to flashing green with the feather on
  target.SetState(Lineside::SignalState::Green, Lineside::SignalFlash::Flashing, 1);
  auto sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, true );
  BOOST_CHECK_EQUAL( feather->lastLevel, true );

  // Call OnRun, green aspect should go out, but feather stays on
  sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, false );
  BOOST_CHECK_EQUAL( feather->lastLevel, true );

  // Call once more, and the green aspect comes back on
  sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, true );
  BOOST_CHECK_EQUAL( feather->lastLevel, true );

  // Now go for steady green without a feather
  target.SetState(Lineside::SignalState::Green, Lineside::SignalFlash::Steady, 0);
  sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, true );
  BOOST_CHECK_EQUAL( feather->lastLevel, false );

  // Deactivate
  target.OnDeactivate();
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, false );
  BOOST_CHECK_EQUAL( feather->lastLevel, false );
}


BOOST_AUTO_TEST_CASE(TwoAspectTwoFeather)
{
  const Lineside::ItemId id(3253);

  // Create the target
  Lineside::DirectDriveMASH target(id);
  target.red = std::make_unique<Tendril::Mocks::MockBOP>();
  target.green = std::make_unique<Tendril::Mocks::MockBOP>();
  target.feathers.push_back(std::make_unique<Tendril::Mocks::MockBOP>());
  target.feathers.push_back(std::make_unique<Tendril::Mocks::MockBOP>());

  // Copy the pointers so that we can see the state 
  auto red = dynamic_cast<Tendril::Mocks::MockBOP*>(target.red.get());
  auto green = dynamic_cast<Tendril::Mocks::MockBOP*>(target.green.get());
  auto feather0 = dynamic_cast<Tendril::Mocks::MockBOP*>(target.feathers.at(0).get());
  auto feather1 = dynamic_cast<Tendril::Mocks::MockBOP*>(target.feathers.at(1).get());
  BOOST_REQUIRE( red );
  BOOST_REQUIRE( green );
  BOOST_REQUIRE( feather0 );
  BOOST_REQUIRE( feather1 );

  // Construction state
  BOOST_CHECK_EQUAL( target.getId(), id );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, false );
  BOOST_CHECK_EQUAL( feather0->lastLevel, false );
  BOOST_CHECK_EQUAL( feather1->lastLevel, false );

  // Activate
  target.OnActivate();
  BOOST_CHECK_EQUAL( red->lastLevel, true );
  BOOST_CHECK_EQUAL( green->lastLevel, false );
  BOOST_CHECK_EQUAL( feather0->lastLevel, false );
  BOOST_CHECK_EQUAL( feather1->lastLevel, false );

  // Set to green with one feather
  target.SetState(Lineside::SignalState::Green, Lineside::SignalFlash::Steady, 1);
  auto sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, true );
  BOOST_CHECK_EQUAL( feather0->lastLevel, true );
  BOOST_CHECK_EQUAL( feather1->lastLevel, false );

  // And green with the other feather
  target.SetState(Lineside::SignalState::Green, Lineside::SignalFlash::Steady, 2);
  sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, true );
  BOOST_CHECK_EQUAL( feather0->lastLevel, false );
  BOOST_CHECK_EQUAL( feather1->lastLevel, true );

  // Green without feathers
  target.SetState(Lineside::SignalState::Green, Lineside::SignalFlash::Steady, 0);
  sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, true );
  BOOST_CHECK_EQUAL( feather0->lastLevel, false );
  BOOST_CHECK_EQUAL( feather1->lastLevel, false );

  // Deactivate
  target.OnDeactivate();
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, false );
  BOOST_CHECK_EQUAL( feather0->lastLevel, false );
  BOOST_CHECK_EQUAL( feather1->lastLevel, false );
}


BOOST_AUTO_TEST_CASE( ThreeAspect )
{
  const Lineside::ItemId id(116731);

  // Create the target
  Lineside::DirectDriveMASH target(id);
  target.red = std::make_unique<Tendril::Mocks::MockBOP>();
  target.yellow1 = std::make_unique<Tendril::Mocks::MockBOP>();
  target.green = std::make_unique<Tendril::Mocks::MockBOP>();

  // Copy the pointers so that we can see the state 
  auto red = dynamic_cast<Tendril::Mocks::MockBOP*>(target.red.get());
  auto yellow = dynamic_cast<Tendril::Mocks::MockBOP*>(target.yellow1.get());
  auto green = dynamic_cast<Tendril::Mocks::MockBOP*>(target.green.get());
  BOOST_REQUIRE( red );
  BOOST_REQUIRE( yellow );
  BOOST_REQUIRE( green );

  // Construction state
  BOOST_CHECK_EQUAL( target.getId(), id );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( yellow->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, false );

  // Activate
  target.OnActivate();
  BOOST_CHECK_EQUAL( red->lastLevel, true );
  BOOST_CHECK_EQUAL( yellow->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, false );

  // Set to yellow and steady
  target.SetState(Lineside::SignalState::Yellow, Lineside::SignalFlash::Steady, 0);
  auto sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( yellow->lastLevel, true );
  BOOST_CHECK_EQUAL( green->lastLevel, false );

  // Deactivate
  target.OnDeactivate();
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( yellow->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, false );
}


BOOST_AUTO_TEST_CASE( FourAspect )
{
  const Lineside::ItemId id(46932);

  // Create the target
  Lineside::DirectDriveMASH target(id);
  target.red = std::make_unique<Tendril::Mocks::MockBOP>();
  target.yellow1 = std::make_unique<Tendril::Mocks::MockBOP>();
  target.yellow2 = std::make_unique<Tendril::Mocks::MockBOP>();
  target.green = std::make_unique<Tendril::Mocks::MockBOP>();

  // Copy the pointers so that we can see the state 
  auto red = dynamic_cast<Tendril::Mocks::MockBOP*>(target.red.get());
  auto yellow1 = dynamic_cast<Tendril::Mocks::MockBOP*>(target.yellow1.get());
  auto yellow2 = dynamic_cast<Tendril::Mocks::MockBOP*>(target.yellow2.get());
  auto green = dynamic_cast<Tendril::Mocks::MockBOP*>(target.green.get());
  BOOST_REQUIRE( red );
  BOOST_REQUIRE( yellow1 );
  BOOST_REQUIRE( yellow2 );
  BOOST_REQUIRE( green );
  
  // Activate
  target.OnActivate();
  BOOST_CHECK_EQUAL( red->lastLevel, true );
  BOOST_CHECK_EQUAL( yellow1->lastLevel, false );
  BOOST_CHECK_EQUAL( yellow2->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, false );

  // Set to single yellow and steady
  target.SetState(Lineside::SignalState::Yellow, Lineside::SignalFlash::Steady, 0);
  auto sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( yellow1->lastLevel, true );
  BOOST_CHECK_EQUAL( yellow2->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, false );

  // Set to double yellow and flashing
  target.SetState(Lineside::SignalState::DoubleYellow, Lineside::SignalFlash::Flashing, 0);
  sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( yellow1->lastLevel, true );
  BOOST_CHECK_EQUAL( yellow2->lastLevel, true );
  BOOST_CHECK_EQUAL( green->lastLevel, false );

  // Call OnRun() again, and check that everything is off
  sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( yellow1->lastLevel, false );
  BOOST_CHECK_EQUAL( yellow2->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, false );

  // One more time, and ensure both yellows are on
  sleepTime = target.OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( yellow1->lastLevel, true );
  BOOST_CHECK_EQUAL( yellow2->lastLevel, true );
  BOOST_CHECK_EQUAL( green->lastLevel, false );

  // Deactivate
  target.OnDeactivate();
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( yellow1->lastLevel, false );
  BOOST_CHECK_EQUAL( yellow2->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, false );
}
  

BOOST_AUTO_TEST_SUITE_END()
