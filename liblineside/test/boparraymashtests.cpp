#include <boost/test/unit_test.hpp>

#include "tendril/mocks/mockboparray.hpp"
#include "tendril/mocks/mockboparrayprovider.hpp"

#include "lineside/boparraymash.hpp"
#include "lineside/boparraymashdata.hpp"

#include "mockmanagerfixture.hpp"

// =======================================

BOOST_FIXTURE_TEST_SUITE(BOPArrayMASH, MockManagerFixture)

BOOST_AUTO_TEST_CASE(TwoAspect)
{
  const Lineside::ItemId id(16);
  
  const size_t redPin = 0;
  const size_t greenPin = 1;

  Lineside::BOPArrayMASHData mashd;
  mashd.id = id;
  mashd.settings["Red"] = std::to_string(redPin);
  mashd.settings["Green"] = std::to_string(greenPin);
  mashd.bopArrayRequest.providerName = "MockBOPArray";
  mashd.bopArrayRequest.idOnProvider = "ArrayForTest";
  mashd.bopArrayRequest.settings[std::to_string(redPin)] = "100";
  mashd.bopArrayRequest.settings[std::to_string(greenPin)] = "128";
  BOOST_TEST_PASSPOINT();

  // Create the target
  auto pwItem = mashd.Construct( *(this->hwManager), *(this->swManager) );
  BOOST_REQUIRE( pwItem );
  auto target = std::dynamic_pointer_cast<Lineside::BOPArrayMASH>(pwItem);
  BOOST_REQUIRE( target );
  BOOST_TEST_PASSPOINT();

  // Get access to the MockBOPArray
  auto hp = this->hwManager->bopArrayProviderRegistrar.Retrieve("MockBOPArray");
  BOOST_REQUIRE( hp );
  auto mbp = std::dynamic_pointer_cast<Tendril::Mocks::MockBOPArrayProvider>(hp);
  BOOST_REQUIRE( mbp );
  auto mba = dynamic_cast<Tendril::Mocks::MockBOPArray*>(mbp->hardware.at("ArrayForTest"));
  BOOST_REQUIRE( mba );

  // Construction state
  BOOST_CHECK_EQUAL( target->getId(), id );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
  
  // Activate
  target->OnActivate();
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
  
  // Set to green
  target->SetState(Lineside::SignalState::Green,
		   Lineside::SignalFlash::Steady,
		   0);
  auto sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), true );

  // Call OnRun again, but we didn't set it flashing
  sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), true );

  // Set to flashing red
  target->SetState(Lineside::SignalState::Red,
		   Lineside::SignalFlash::Flashing,
		   0);
  sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );

  // Call OnRun again, and this time we are flashing
  sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );

  // And one more time, since the aspect should be back on
  sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );

  // Deactivate
  target->OnDeactivate();
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
}

BOOST_AUTO_TEST_CASE(TwoAspectOneFeather)
{
  const Lineside::ItemId id(15);
    
  const size_t redPin = 0;
  const size_t greenPin = 2;
  const size_t featherPin = 1;

  Lineside::BOPArrayMASHData mashd;
  mashd.id = id;
  mashd.settings["Red"] = std::to_string(redPin);
  mashd.settings["Green"] = std::to_string(greenPin);
  mashd.settings["Feather1"] = std::to_string(featherPin);
  mashd.bopArrayRequest.providerName = "MockBOPArray";
  mashd.bopArrayRequest.idOnProvider = "ArrayForTest";
  mashd.bopArrayRequest.settings[std::to_string(redPin)] = "100";
  mashd.bopArrayRequest.settings[std::to_string(greenPin)] = "128";
  mashd.bopArrayRequest.settings[std::to_string(featherPin)] = "129";
  BOOST_TEST_PASSPOINT();

  // Create the target
  auto pwItem = mashd.Construct( *(this->hwManager), *(this->swManager) );
  BOOST_REQUIRE( pwItem );
  auto target = std::dynamic_pointer_cast<Lineside::BOPArrayMASH>(pwItem);
  BOOST_REQUIRE( target );
  BOOST_TEST_PASSPOINT();

  // Get access to the MockBOPArray
  auto hp = this->hwManager->bopArrayProviderRegistrar.Retrieve("MockBOPArray");
  BOOST_REQUIRE( hp );
  auto mbp = std::dynamic_pointer_cast<Tendril::Mocks::MockBOPArrayProvider>(hp);
  BOOST_REQUIRE( mbp );
  auto mba = dynamic_cast<Tendril::Mocks::MockBOPArray*>(mbp->hardware.at("ArrayForTest"));
  BOOST_REQUIRE( mba );

  // Construction state
  BOOST_CHECK_EQUAL( target->getId(), id );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin), false );
  
  // Activate
  target->OnActivate();
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin), false );
  
  // Set to flashing green with the feather on
  target->SetState(Lineside::SignalState::Green,
		   Lineside::SignalFlash::Flashing,
		   1);
  auto sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin), true );

  // Call OnRun, green aspect should go out, but feather stays on
  sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin), true );

  // Call once more, and the green aspect comes back on
  sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin), true );
  
  // Now go for steady green without a feather
  target->SetState(Lineside::SignalState::Green,
		   Lineside::SignalFlash::Steady,
		   0);
  sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin), false );
  
  // Deactivate
  target->OnDeactivate();
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin), false );
}

BOOST_AUTO_TEST_CASE(TwoAspectTwoFeather)
{
  const Lineside::ItemId id(3253);
  const size_t redPin = 1;
  const size_t greenPin = 2;
  const size_t featherPin1 = 3;
  const size_t featherPin2 = 0;
  
  Lineside::BOPArrayMASHData mashd;
  mashd.id = id;
  mashd.settings["Red"] = std::to_string(redPin);
  mashd.settings["Green"] = std::to_string(greenPin);
  mashd.settings["Feather1"] = std::to_string(featherPin1);
  mashd.settings["Feather2"] = std::to_string(featherPin2);
  mashd.bopArrayRequest.providerName = "MockBOPArray";
  mashd.bopArrayRequest.idOnProvider = "ArrayForTest";
  mashd.bopArrayRequest.settings[std::to_string(redPin)] = "100";
  mashd.bopArrayRequest.settings[std::to_string(greenPin)] = "128";
  mashd.bopArrayRequest.settings[std::to_string(featherPin1)] = "129";
  mashd.bopArrayRequest.settings[std::to_string(featherPin2)] = "144";
  BOOST_TEST_PASSPOINT();

  // Create the target
  auto pwItem = mashd.Construct( *(this->hwManager), *(this->swManager) );
  BOOST_REQUIRE( pwItem );
  auto target = std::dynamic_pointer_cast<Lineside::BOPArrayMASH>(pwItem);
  BOOST_REQUIRE( target );
  BOOST_TEST_PASSPOINT();

  // Get access to the MockBOPArray
  auto hp = this->hwManager->bopArrayProviderRegistrar.Retrieve("MockBOPArray");
  BOOST_REQUIRE( hp );
  auto mbp = std::dynamic_pointer_cast<Tendril::Mocks::MockBOPArrayProvider>(hp);
  BOOST_REQUIRE( mbp );
  auto mba = dynamic_cast<Tendril::Mocks::MockBOPArray*>(mbp->hardware.at("ArrayForTest"));
  BOOST_REQUIRE( mba );

  // Construction state
  BOOST_CHECK_EQUAL( target->getId(), id );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin1), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin2), false );

  // Activate
  target->OnActivate();
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin1), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin2), false );

  // Set to green with one feather
  target->SetState(Lineside::SignalState::Green,
		   Lineside::SignalFlash::Steady,
		   1);
  auto sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin1), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin2), false );

  // And green with the other feather
  target->SetState(Lineside::SignalState::Green,
		   Lineside::SignalFlash::Steady,
		   2);
  sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin1), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin2), true );
  
  // Green without feathers
  target->SetState(Lineside::SignalState::Green,
		   Lineside::SignalFlash::Steady,
		   0);
  sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin1), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin2), false );

  // Deactivate
  target->OnDeactivate();
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin1), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(featherPin2), false );
}

BOOST_AUTO_TEST_CASE(ThreeAspect)
{
  const Lineside::ItemId id(116731);
  const size_t redPin = 1;
  const size_t yellowPin = 0;
  const size_t greenPin = 2;

  Lineside::BOPArrayMASHData mashd;
  mashd.id = id;
  mashd.settings["Red"] = std::to_string(redPin);
  mashd.settings["Green"] = std::to_string(greenPin);
  mashd.settings["Yellow1"] = std::to_string(yellowPin);
  mashd.bopArrayRequest.providerName = "MockBOPArray";
  mashd.bopArrayRequest.idOnProvider = "ArrayForTest";
  mashd.bopArrayRequest.settings[std::to_string(redPin)] = "100";
  mashd.bopArrayRequest.settings[std::to_string(greenPin)] = "128";
  mashd.bopArrayRequest.settings[std::to_string(yellowPin)] = "129";
  BOOST_TEST_PASSPOINT();

  // Create the target
  auto pwItem = mashd.Construct( *(this->hwManager), *(this->swManager) );
  BOOST_REQUIRE( pwItem );
  auto target = std::dynamic_pointer_cast<Lineside::BOPArrayMASH>(pwItem);
  BOOST_REQUIRE( target );
  BOOST_TEST_PASSPOINT();

  // Get access to the MockBOPArray
  auto hp = this->hwManager->bopArrayProviderRegistrar.Retrieve("MockBOPArray");
  BOOST_REQUIRE( hp );
  auto mbp = std::dynamic_pointer_cast<Tendril::Mocks::MockBOPArrayProvider>(hp);
  BOOST_REQUIRE( mbp );
  auto mba = dynamic_cast<Tendril::Mocks::MockBOPArray*>(mbp->hardware.at("ArrayForTest"));
  BOOST_REQUIRE( mba );
  
  // Construction state
  BOOST_CHECK_EQUAL( target->getId(), id );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellowPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
  
  // Activate
  target->OnActivate();
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellowPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
  
  // Set to yellow and steady
  target->SetState(Lineside::SignalState::Yellow, Lineside::SignalFlash::Steady, 0);
  auto sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellowPin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
  
  // Deactivate
  target->OnDeactivate();
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellowPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
}

BOOST_AUTO_TEST_CASE(FourAspect)
{
  const Lineside::ItemId id(115);
  const size_t redPin = 1;
  const size_t yellow1Pin = 0;
  const size_t yellow2Pin = 3;
  const size_t greenPin = 2;

  Lineside::BOPArrayMASHData mashd;
  mashd.id = id;
  mashd.settings["Red"] = std::to_string(redPin);
  mashd.settings["Green"] = std::to_string(greenPin);
  mashd.settings["Yellow1"] = std::to_string(yellow1Pin);
  mashd.settings["Yellow2"] = std::to_string(yellow2Pin);
  mashd.bopArrayRequest.providerName = "MockBOPArray";
  mashd.bopArrayRequest.idOnProvider = "ArrayForTest";
  mashd.bopArrayRequest.settings[std::to_string(redPin)] = "100";
  mashd.bopArrayRequest.settings[std::to_string(greenPin)] = "128";
  mashd.bopArrayRequest.settings[std::to_string(yellow1Pin)] = "129";
  mashd.bopArrayRequest.settings[std::to_string(yellow2Pin)] = "132";
  BOOST_TEST_PASSPOINT();

  // Create the target
  auto pwItem = mashd.Construct( *(this->hwManager), *(this->swManager) );
  BOOST_REQUIRE( pwItem );
  auto target = std::dynamic_pointer_cast<Lineside::BOPArrayMASH>(pwItem);
  BOOST_REQUIRE( target );
  BOOST_TEST_PASSPOINT();

  // Get access to the MockBOPArray
  auto hp = this->hwManager->bopArrayProviderRegistrar.Retrieve("MockBOPArray");
  BOOST_REQUIRE( hp );
  auto mbp = std::dynamic_pointer_cast<Tendril::Mocks::MockBOPArrayProvider>(hp);
  BOOST_REQUIRE( mbp );
  auto mba = dynamic_cast<Tendril::Mocks::MockBOPArray*>(mbp->hardware.at("ArrayForTest"));
  BOOST_REQUIRE( mba );

  // Construction state
  BOOST_CHECK_EQUAL( target->getId(), id );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellow1Pin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellow2Pin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );

  // Activate
  target->OnActivate();
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellow1Pin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellow2Pin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );

  // Set to single yellow and steady
  target->SetState(Lineside::SignalState::Yellow, Lineside::SignalFlash::Steady, 0);
  auto sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellow1Pin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellow2Pin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
  
  // Set to double yellow and flashing
  target->SetState(Lineside::SignalState::DoubleYellow, Lineside::SignalFlash::Flashing, 0);
  sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellow1Pin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellow2Pin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );

  // Call OnRun() again, and check that everything is off
  sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellow1Pin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellow2Pin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );

  // One more time, and ensure both yellows are on
  sleepTime = target->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellow1Pin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellow2Pin), true );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );

  // Deactivate
  target->OnDeactivate();
  BOOST_CHECK_EQUAL( mba->outputs.at(redPin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellow1Pin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(yellow2Pin), false );
  BOOST_CHECK_EQUAL( mba->outputs.at(greenPin), false );
}
  
BOOST_AUTO_TEST_SUITE_END()
