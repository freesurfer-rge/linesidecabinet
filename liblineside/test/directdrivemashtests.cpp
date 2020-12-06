#include <set>

#include <boost/test/unit_test.hpp>

#include "tendril/mocks/mockbop.hpp"
#include "tendril/mocks/mockhardwareprovider.hpp"

#include "lineside/directdrivemash.hpp"
#include "lineside/directdrivemashdata.hpp"
#include "lineside/linesideexceptions.hpp"

#include "mockmanagerfixture.hpp"

typedef Tendril::Mocks::MockHardwareProvider<Tendril::BinaryOutputPin,
					     Tendril::Mocks::MockBOP> MockBOPProvider;

// =====================================

/*
  Note that the "BadState" tests are actually for MultiAspectSignalHead
  base class, which contains the state checks
*/
void CheckBadState(Lineside::DirectDriveMASH& target,
		   const Lineside::SignalState badState,
		   const Lineside::SignalFlash flash, // Can't be 'bad'
		   const unsigned int badFeather) {
  const Lineside::ItemId targetId = target.getId();
  auto fn = [=](const Lineside::InvalidMASHStateException& imse) {
    BOOST_CHECK_EQUAL( imse.target, targetId );
    BOOST_CHECK_EQUAL( imse.state, badState );
    BOOST_CHECK_EQUAL( imse.flash, flash );
    BOOST_CHECK_EQUAL( imse.feather, badFeather );
    return (imse.state==badState) && (imse.flash==flash) && (imse.feather==badFeather);
  };
  
  BOOST_CHECK_EXCEPTION( target.SetState(badState, flash, badFeather),
			 Lineside::InvalidMASHStateException,
			 fn );
}

// =====================================

BOOST_FIXTURE_TEST_SUITE(DirectDriveMASH, MockManagerFixture)

BOOST_AUTO_TEST_CASE(TwoAspect)
{
  const Lineside::ItemId id(11);

  Lineside::DirectDriveMASHData mashd;
  mashd.id = id;

  Lineside::DeviceRequestData drd;
  drd.controller = "MockBOP";
  drd.controllerData = "10";
  mashd.aspectRequests[Lineside::SignalAspect::Red] = drd;
  drd.controllerData = "11";
  mashd.aspectRequests[Lineside::SignalAspect::Green] = drd;
  
  // Create the target
  auto pwItem = mashd.Construct( *(this->hwManager), *(this->swManager) );
  BOOST_REQUIRE( pwItem );
  auto target = std::dynamic_pointer_cast<Lineside::DirectDriveMASH>(pwItem);
  BOOST_REQUIRE( target );
  
  // Copy the pointers so that we can see the state
  auto hp = this->hwManager->bopProviderRegistrar.Retrieve("MockBOP");
  BOOST_REQUIRE( hp );
  auto mbp = std::dynamic_pointer_cast<MockBOPProvider>(hp);
  BOOST_REQUIRE( hp );
  auto red = mbp->hardware.at("10");
  auto green = mbp->hardware.at("11");
  BOOST_REQUIRE( red );
  BOOST_REQUIRE( green );

  // Construction state
  BOOST_CHECK_EQUAL( target->getId(), id );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, false );

  // Activate
  target->OnActivate();
  BOOST_CHECK_EQUAL( red->lastLevel, true );
  BOOST_CHECK_EQUAL( green->lastLevel, false );
  
  // Set to green
  target->SetState(Lineside::SignalState::Green, Lineside::SignalFlash::Steady, 0);
  auto sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, true );

  // Call OnRun again, but we didn't set it flashing
  sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, true );

  // Set to flashing red
  target->SetState(Lineside::SignalState::Red, Lineside::SignalFlash::Flashing, 0);
  sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, true );
  BOOST_CHECK_EQUAL( green->lastLevel, false );

  // Call OnRun again, and this time we are flashing
  sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, false );

  // And one more time, since the aspect should be back on
  sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, true );
  BOOST_CHECK_EQUAL( green->lastLevel, false );

  // Deactivate
  target->OnDeactivate();
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, false );
}

BOOST_AUTO_TEST_CASE(TwoAspectOneFeather)
{
  const Lineside::ItemId id(15);

  Lineside::DirectDriveMASHData mashd;
  mashd.id = id;

  Lineside::DeviceRequestData drd;
  drd.controller = "MockBOP";
  drd.controllerData = "10";
  mashd.aspectRequests[Lineside::SignalAspect::Red] = drd;
  drd.controllerData = "11";
  mashd.aspectRequests[Lineside::SignalAspect::Green] = drd;
  drd.controllerData = "19";
  mashd.featherRequests[1] = drd;
  
  // Create the target
  auto pwItem = mashd.Construct( *(this->hwManager), *(this->swManager) );
  BOOST_REQUIRE( pwItem );
  auto target = std::dynamic_pointer_cast<Lineside::DirectDriveMASH>(pwItem);
  BOOST_REQUIRE( target );
  
  // Copy the pointers so that we can see the state
  auto hp = this->hwManager->bopProviderRegistrar.Retrieve("MockBOP");
  BOOST_REQUIRE( hp );
  auto mbp = std::dynamic_pointer_cast<MockBOPProvider>(hp);
  BOOST_REQUIRE( hp );
  auto red = mbp->hardware.at("10");
  auto green = mbp->hardware.at("11");
  auto feather = mbp->hardware.at("19");
  BOOST_REQUIRE( red );
  BOOST_REQUIRE( green );
  BOOST_REQUIRE( feather );

  // Construction state
  BOOST_CHECK_EQUAL( target->getId(), id );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, false );
  BOOST_CHECK_EQUAL( feather->lastLevel, false );

  // Activate
  target->OnActivate();
  BOOST_CHECK_EQUAL( red->lastLevel, true );
  BOOST_CHECK_EQUAL( green->lastLevel, false );
  BOOST_CHECK_EQUAL( feather->lastLevel, false );

  // Set to flashing green with the feather on
  target->SetState(Lineside::SignalState::Green, Lineside::SignalFlash::Flashing, 1);
  auto sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, true );
  BOOST_CHECK_EQUAL( feather->lastLevel, true );

  // Call OnRun, green aspect should go out, but feather stays on
  sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, false );
  BOOST_CHECK_EQUAL( feather->lastLevel, true );

  // Call once more, and the green aspect comes back on
  sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, true );
  BOOST_CHECK_EQUAL( feather->lastLevel, true );

  // Now go for steady green without a feather
  target->SetState(Lineside::SignalState::Green, Lineside::SignalFlash::Steady, 0);
  sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, true );
  BOOST_CHECK_EQUAL( feather->lastLevel, false );

  // Deactivate
  target->OnDeactivate();
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, false );
  BOOST_CHECK_EQUAL( feather->lastLevel, false );
}

BOOST_AUTO_TEST_CASE(TwoAspectTwoFeather)
{
  const Lineside::ItemId id(3253);

  Lineside::DirectDriveMASHData mashd;
  mashd.id = id;

  Lineside::DeviceRequestData drd;
  drd.controller = "MockBOP";
  drd.controllerData = "10";
  mashd.aspectRequests[Lineside::SignalAspect::Red] = drd;
  drd.controllerData = "11";
  mashd.aspectRequests[Lineside::SignalAspect::Green] = drd;
  drd.controllerData = "19";
  mashd.featherRequests[1] = drd;
  drd.controllerData = "21";
  mashd.featherRequests[2] = drd;
  
  // Create the target
  auto pwItem = mashd.Construct( *(this->hwManager), *(this->swManager) );
  BOOST_REQUIRE( pwItem );
  auto target = std::dynamic_pointer_cast<Lineside::DirectDriveMASH>(pwItem);
  BOOST_REQUIRE( target );
  
  // Copy the pointers so that we can see the state
  auto hp = this->hwManager->bopProviderRegistrar.Retrieve("MockBOP");
  BOOST_REQUIRE( hp );
  auto mbp = std::dynamic_pointer_cast<MockBOPProvider>(hp);
  BOOST_REQUIRE( hp );
  auto red = mbp->hardware.at("10");
  auto green = mbp->hardware.at("11");
  auto feather1 = mbp->hardware.at("19");
  auto feather2 = mbp->hardware.at("21");
  BOOST_REQUIRE( red );
  BOOST_REQUIRE( green );
  BOOST_REQUIRE( feather1 );
  BOOST_REQUIRE( feather2 );
  
  // Construction state
  BOOST_CHECK_EQUAL( target->getId(), id );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, false );
  BOOST_CHECK_EQUAL( feather1->lastLevel, false );
  BOOST_CHECK_EQUAL( feather2->lastLevel, false );

  // Activate
  target->OnActivate();
  BOOST_CHECK_EQUAL( red->lastLevel, true );
  BOOST_CHECK_EQUAL( green->lastLevel, false );
  BOOST_CHECK_EQUAL( feather1->lastLevel, false );
  BOOST_CHECK_EQUAL( feather2->lastLevel, false );

  // Set to green with one feather
  target->SetState(Lineside::SignalState::Green, Lineside::SignalFlash::Steady, 1);
  auto sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, true );
  BOOST_CHECK_EQUAL( feather1->lastLevel, true );
  BOOST_CHECK_EQUAL( feather2->lastLevel, false );

  // And green with the other feather
  target->SetState(Lineside::SignalState::Green, Lineside::SignalFlash::Steady, 2);
  sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, true );
  BOOST_CHECK_EQUAL( feather1->lastLevel, false );
  BOOST_CHECK_EQUAL( feather2->lastLevel, true );

  // Green without feathers
  target->SetState(Lineside::SignalState::Green, Lineside::SignalFlash::Steady, 0);
  sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, true );
  BOOST_CHECK_EQUAL( feather1->lastLevel, false );
  BOOST_CHECK_EQUAL( feather2->lastLevel, false );

  // Deactivate
  target->OnDeactivate();
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, false );
  BOOST_CHECK_EQUAL( feather1->lastLevel, false );
  BOOST_CHECK_EQUAL( feather2->lastLevel, false );
}

BOOST_AUTO_TEST_CASE( TwoAspectBadState )
{
  const Lineside::ItemId id(15);
  
  Lineside::DirectDriveMASHData mashd;
  mashd.id = id;

  Lineside::DeviceRequestData drd;
  drd.controller = "MockBOP";
  drd.controllerData = "10";
  mashd.aspectRequests[Lineside::SignalAspect::Red] = drd;
  drd.controllerData = "11";
  mashd.aspectRequests[Lineside::SignalAspect::Green] = drd;
  drd.controllerData = "19";
  mashd.featherRequests[1] = drd;
  
  // Create the target
  auto pwItem = mashd.Construct( *(this->hwManager), *(this->swManager) );
  BOOST_REQUIRE( pwItem );
  auto target = std::dynamic_pointer_cast<Lineside::DirectDriveMASH>(pwItem);
  BOOST_REQUIRE( target );

  BOOST_TEST_CONTEXT( "Checking aspects" ) {
    CheckBadState(*target, Lineside::SignalState::Yellow, Lineside::SignalFlash::Steady, 0);
    CheckBadState(*target, Lineside::SignalState::DoubleYellow, Lineside::SignalFlash::Steady, 0);
  }
  BOOST_TEST_CONTEXT( "Checking feather" ) {
    CheckBadState(*target, Lineside::SignalState::Green, Lineside::SignalFlash::Steady, 2);
  }
}

BOOST_AUTO_TEST_CASE( ThreeAspect )
{
  const Lineside::ItemId id(116731);

  Lineside::DirectDriveMASHData mashd;
  mashd.id = id;

  Lineside::DeviceRequestData drd;
  drd.controller = "MockBOP";
  drd.controllerData = "15";
  mashd.aspectRequests[Lineside::SignalAspect::Red] = drd;
  drd.controllerData = "16";
  mashd.aspectRequests[Lineside::SignalAspect::Green] = drd;
  drd.controllerData = "10";
  mashd.aspectRequests[Lineside::SignalAspect::Yellow1] = drd;
  
  // Create the target
  auto pwItem = mashd.Construct( *(this->hwManager), *(this->swManager) );
  BOOST_REQUIRE( pwItem );
  auto target = std::dynamic_pointer_cast<Lineside::DirectDriveMASH>(pwItem);
  BOOST_REQUIRE( target );

  // Copy the pointers so that we can see the state
  auto hp = this->hwManager->bopProviderRegistrar.Retrieve("MockBOP");
  BOOST_REQUIRE( hp );
  auto mbp = std::dynamic_pointer_cast<MockBOPProvider>(hp);
  BOOST_REQUIRE( hp );
  auto red = mbp->hardware.at("15");
  auto green = mbp->hardware.at("16");
  auto yellow1 = mbp->hardware.at("10");
  BOOST_REQUIRE( red );
  BOOST_REQUIRE( green );
  BOOST_REQUIRE( yellow1 );

  // Construction state
  BOOST_CHECK_EQUAL( target->getId(), id );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( yellow1->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, false );

  // Activate
  target->OnActivate();
  BOOST_CHECK_EQUAL( red->lastLevel, true );
  BOOST_CHECK_EQUAL( yellow1->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, false );

  // Set to yellow and steady
  target->SetState(Lineside::SignalState::Yellow, Lineside::SignalFlash::Steady, 0);
  auto sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( yellow1->lastLevel, true );
  BOOST_CHECK_EQUAL( green->lastLevel, false );

  // Deactivate
  target->OnDeactivate();
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( yellow1->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, false );
}


BOOST_AUTO_TEST_CASE( ThreeAspectBadState )
{
  const Lineside::ItemId id(115);

  Lineside::DirectDriveMASHData mashd;
  mashd.id = id;

  Lineside::DeviceRequestData drd;
  drd.controller = "MockBOP";
  drd.controllerData = "15";
  mashd.aspectRequests[Lineside::SignalAspect::Red] = drd;
  drd.controllerData = "16";
  mashd.aspectRequests[Lineside::SignalAspect::Green] = drd;
  drd.controllerData = "10";
  mashd.aspectRequests[Lineside::SignalAspect::Yellow1] = drd;
  drd.controllerData = "11";
  mashd.featherRequests[1] = drd;
  
  // Create the target
  auto pwItem = mashd.Construct( *(this->hwManager), *(this->swManager) );
  BOOST_REQUIRE( pwItem );
  auto target = std::dynamic_pointer_cast<Lineside::DirectDriveMASH>(pwItem);
  BOOST_REQUIRE( target );

  BOOST_TEST_CONTEXT( "Checking aspects" ) {
    CheckBadState(*target, Lineside::SignalState::DoubleYellow, Lineside::SignalFlash::Steady, 0);
  }
  BOOST_TEST_CONTEXT( "Checking feather" ) {
    CheckBadState(*target, Lineside::SignalState::Green, Lineside::SignalFlash::Steady, 2);
  }
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

  // Construction state
  BOOST_CHECK_EQUAL( target.getId(), id );
  BOOST_CHECK_EQUAL( red->lastLevel, false );
  BOOST_CHECK_EQUAL( yellow1->lastLevel, false );
  BOOST_CHECK_EQUAL( yellow2->lastLevel, false );
  BOOST_CHECK_EQUAL( green->lastLevel, false );
  
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
