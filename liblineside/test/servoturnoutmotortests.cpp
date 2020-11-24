#include <boost/test/unit_test.hpp>

#include "tendril/mocks/mockhardwareprovider.hpp"
#include "tendril/mocks/mockpwmchannel.hpp"
#include "tendril/mocks/utilities.hpp"

#include "lineside/servoturnoutmotordata.hpp"
#include "lineside/servoturnoutmotor.hpp"

#include "notifytarget.hpp"
#include "mockmanagerfixture.hpp"

BOOST_FIXTURE_TEST_SUITE(ServoTurnoutMotor, MockManagerFixture)

BOOST_AUTO_TEST_CASE(Construct)
{
  const Lineside::ItemId id(10);
  const unsigned int straight = 10;
  const unsigned int curved = 113;
  const std::string controller = Tendril::Mocks::PWMCProviderId;
  const std::string controllerData = "07";
  
  Lineside::ServoTurnoutMotorData stmd;
  stmd.id = id;
  stmd.straight = straight;
  stmd.curved = curved;
  stmd.pwmChannelRequest.controller = controller;
  stmd.pwmChannelRequest.controllerData = controllerData;

  auto pwItem = stmd.Construct(*(this->hwManager), *(this->swManager));
  BOOST_REQUIRE( pwItem );
  BOOST_CHECK_EQUAL( pwItem->getId(), id );
  auto stm = std::dynamic_pointer_cast<Lineside::ServoTurnoutMotor>(pwItem);
  BOOST_REQUIRE( stm );
  BOOST_REQUIRE_EQUAL( stm.use_count(), 2 ); // pwItem and stm itself
}

BOOST_AUTO_TEST_CASE(OnActivateSetsStraight)
{
  const Lineside::ItemId id(10);
  const unsigned int straight = 10;
  const unsigned int curved = 113;
  const std::string controller = Tendril::Mocks::PWMCProviderId;
  const std::string controllerData = "07";
  
  Lineside::ServoTurnoutMotorData stmd;
  stmd.id = id;
  stmd.straight = straight;
  stmd.curved = curved;
  stmd.pwmChannelRequest.controller = controller;
  stmd.pwmChannelRequest.controllerData = controllerData;

  auto pwItem = stmd.Construct(*(this->hwManager), *(this->swManager));
  BOOST_REQUIRE( pwItem );
  BOOST_CHECK_EQUAL( pwItem->getId(), id );
  auto stm = std::dynamic_pointer_cast<Lineside::ServoTurnoutMotor>(pwItem);
  BOOST_REQUIRE( stm );

  // Call the onActivate method
  pwItem->OnActivate();
  
  BOOST_CHECK_EQUAL( stm->GetState(), Lineside::TurnoutState::Straight );
  auto mockProvider = this->hwManager->pwmcProviderRegistrar.Retrieve(controller);
  auto mockpwmcProvider = std::dynamic_pointer_cast<Tendril::Mocks::MockHardwareProvider<Tendril::PWMChannel, Tendril::Mocks::MockPWMChannel>>(mockProvider);
  auto pwmChannel = mockpwmcProvider->hardware.at(controllerData);
  auto lastUpdate = pwmChannel->updates.back();
  BOOST_CHECK_EQUAL( lastUpdate.first, 0 );
  BOOST_CHECK_EQUAL( lastUpdate.second, straight );
}

BOOST_AUTO_TEST_CASE(SetStateAndStateChange)
{
  const unsigned int notifySrcId = 1235;
  std::shared_ptr<NotifyTarget> nt = std::make_shared<NotifyTarget>();
  
  const Lineside::ItemId id(10);
  const unsigned int straight = 10;
  const unsigned int curved = 113;
  const std::string controller = Tendril::Mocks::PWMCProviderId;
  const std::string controllerData = "07";
  
  Lineside::ServoTurnoutMotorData stmd;
  stmd.id = id;
  stmd.straight = straight;
  stmd.curved = curved;
  stmd.pwmChannelRequest.controller = controller;
  stmd.pwmChannelRequest.controllerData = controllerData;

  auto pwItem = stmd.Construct(*(this->hwManager), *(this->swManager));
  pwItem->RegisterController(notifySrcId, nt);
  BOOST_REQUIRE( pwItem );
  BOOST_CHECK_EQUAL( pwItem->getId(), id );
  auto stm = std::dynamic_pointer_cast<Lineside::ServoTurnoutMotor>(pwItem);
  BOOST_REQUIRE( stm );

  // Call the onActivate method
  pwItem->OnActivate();

  // Things should be consistent now
  BOOST_CHECK(!pwItem->HaveStateChange());

  // Change the desired state
  nt->lastNotificationSource = 0;
  nt->lastNotification = false;
  stm->SetState(Lineside::TurnoutState::Curved);
  BOOST_CHECK_EQUAL( nt->lastNotificationSource, notifySrcId );
  BOOST_CHECK_EQUAL( nt->lastNotification, true );
  // However, the actual state never changed
  auto mockProvider = this->hwManager->pwmcProviderRegistrar.Retrieve(controller);
  auto mockpwmcProvider = std::dynamic_pointer_cast<Tendril::Mocks::MockHardwareProvider<Tendril::PWMChannel, Tendril::Mocks::MockPWMChannel>>(mockProvider);
  auto pwmChannel = mockpwmcProvider->hardware.at(controllerData);
  BOOST_CHECK_EQUAL( stm->GetState(), Lineside::TurnoutState::Straight );
  auto lastUpdate = pwmChannel->updates.back();
  BOOST_CHECK_EQUAL( lastUpdate.first, 0 );
  BOOST_CHECK_EQUAL( lastUpdate.second, straight );
  
  // Check that we're indicating an update
  BOOST_CHECK(pwItem->HaveStateChange());

  // Go back to straight
  nt->lastNotificationSource = 0;
  nt->lastNotification = false;
  stm->SetState(Lineside::TurnoutState::Straight);
  BOOST_CHECK_EQUAL( nt->lastNotificationSource, notifySrcId );
  BOOST_CHECK_EQUAL( nt->lastNotification, true );

  // Since the actual internal currentState never changed...
  BOOST_CHECK_EQUAL( stm->GetState(), Lineside::TurnoutState::Straight );
  lastUpdate = pwmChannel->updates.back();
  BOOST_CHECK_EQUAL( lastUpdate.first, 0 );
  BOOST_CHECK_EQUAL( lastUpdate.second, straight );
  BOOST_CHECK(!pwItem->HaveStateChange());
}


BOOST_AUTO_TEST_CASE(SetCurvedAndStraight)
{
  const unsigned int notifySrcId = 1235;
  std::shared_ptr<NotifyTarget> nt = std::make_shared<NotifyTarget>();
  
  const Lineside::ItemId id(10);
  const unsigned int straight = 10;
  const unsigned int curved = 113;
  const std::string controller =  Tendril::Mocks::PWMCProviderId;
  const std::string controllerData = "07";
  
  Lineside::ServoTurnoutMotorData stmd;
  stmd.id = id;
  stmd.straight = straight;
  stmd.curved = curved;
  stmd.pwmChannelRequest.controller = controller;
  stmd.pwmChannelRequest.controllerData = controllerData;

  auto pwItem = stmd.Construct(*(this->hwManager), *(this->swManager));
  pwItem->RegisterController(notifySrcId, nt);
  BOOST_REQUIRE( pwItem );
  BOOST_CHECK_EQUAL( pwItem->getId(), id );
  auto stm = std::dynamic_pointer_cast<Lineside::ServoTurnoutMotor>(pwItem);
  BOOST_REQUIRE( stm );
  auto mockProvider = this->hwManager->pwmcProviderRegistrar.Retrieve(controller);
  auto mockpwmcProvider = std::dynamic_pointer_cast<Tendril::Mocks::MockHardwareProvider<Tendril::PWMChannel, Tendril::Mocks::MockPWMChannel>>(mockProvider);
  auto pwmChannel = mockpwmcProvider->hardware.at(controllerData);
  BOOST_REQUIRE( pwmChannel );

  // Call the onActivate method
  pwItem->OnActivate();

  // Clear the pwmChannel updates
  pwmChannel->updates.clear();

  // Indicate that we want to change state to Curved
  stm->SetState(Lineside::TurnoutState::Curved);

  auto start = std::chrono::high_resolution_clock::now();
  auto requestedSleep = stm->OnRun();
  auto stop = std::chrono::high_resolution_clock::now();

  // Check we got to the right place
  auto lastPosition = pwmChannel->updates.back();
  BOOST_CHECK_EQUAL( lastPosition.first, 0 );
  BOOST_CHECK_EQUAL( lastPosition.second, curved );
  BOOST_CHECK_EQUAL( stm->GetState(), Lineside::TurnoutState::Curved );

  // Check we took an appropriate time
  BOOST_CHECK_EQUAL( stm->MoveSteps, 10 );
  // We move to MoveSteps positions, so there are MoveSteps-1 intervals
  BOOST_CHECK( stop-start >= stm->MoveSleep*(stm->MoveSteps-1) );
  // Check that the correct sleep was requested
  BOOST_CHECK( requestedSleep == stm->SleepInterval );

  // Now examine the set of updates to the pwmChannel
  BOOST_REQUIRE_EQUAL( pwmChannel->updates.size(), stm->MoveSteps );

  for( size_t i=1; i<pwmChannel->updates.size(); i++ ) {
    auto prev = pwmChannel->updates.at(i-1);
    auto curr = pwmChannel->updates.at(i);
    BOOST_CHECK_EQUAL( curr.first, 0 );
    BOOST_CHECK_EQUAL( prev.first, 0 );
    // Since curved > straight above...
    BOOST_CHECK_GT( curr.second, prev.second );
    BOOST_CHECK_GE( prev.second, straight );
    BOOST_CHECK_LE( prev.second, curved );
  }

  // Now, repeat everything to go back to straight

  pwmChannel->updates.clear();
  stm->SetState(Lineside::TurnoutState::Straight);
  start = std::chrono::high_resolution_clock::now();
  requestedSleep = stm->OnRun();
  stop = std::chrono::high_resolution_clock::now();

  lastPosition = pwmChannel->updates.back();
  BOOST_CHECK_EQUAL( lastPosition.first, 0 );
  BOOST_CHECK_EQUAL( lastPosition.second, straight );
  BOOST_CHECK_EQUAL( stm->GetState(), Lineside::TurnoutState::Straight );
  BOOST_CHECK( stop-start >= stm->MoveSleep*(stm->MoveSteps-1) );
  BOOST_CHECK( requestedSleep == stm->SleepInterval );
  
  BOOST_REQUIRE_EQUAL( pwmChannel->updates.size(), stm->MoveSteps );
  for( size_t i=1; i<pwmChannel->updates.size(); i++ ) {
    auto prev = pwmChannel->updates.at(i-1);
    auto curr = pwmChannel->updates.at(i);
    BOOST_CHECK_EQUAL( curr.first, 0 );
    BOOST_CHECK_EQUAL( prev.first, 0 );
    // Since curved > straight above...
    BOOST_CHECK_LT( curr.second, prev.second );
    BOOST_CHECK_GE( prev.second, straight );
    BOOST_CHECK_LE( prev.second, curved );
  }
}

BOOST_AUTO_TEST_SUITE_END()
