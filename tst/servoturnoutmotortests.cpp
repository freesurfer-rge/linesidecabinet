#include <boost/test/unit_test.hpp>

#include "servoturnoutmotordata.hpp"
#include "servoturnoutmotor.hpp"

#include "notifytarget.hpp"
#include "mockhardwaremanagerfixture.hpp"

BOOST_FIXTURE_TEST_SUITE(ServoTurnoutMotor, MockHardwareManagerFixture)

BOOST_AUTO_TEST_CASE(Construct)
{
  const Lineside::ItemId id(10);
  const unsigned int straight = 10;
  const unsigned int curved = 113;
  const std::string controller = "MockPWMController";
  const std::string controllerData = "07";
  
  Lineside::ServoTurnoutMotorData stmd;
  stmd.id = id;
  stmd.straight = straight;
  stmd.curved = curved;
  stmd.pwmChannelRequest.controller = this->hwManager->PWMChannelProviderId;
  stmd.pwmChannelRequest.controllerData = controllerData;

  auto pwItem = stmd.Construct(this->hwManager);
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
  const std::string controller = "MockPWMController";
  const std::string controllerData = "07";
  
  Lineside::ServoTurnoutMotorData stmd;
  stmd.id = id;
  stmd.straight = straight;
  stmd.curved = curved;
  stmd.pwmChannelRequest.controller = this->hwManager->PWMChannelProviderId;
  stmd.pwmChannelRequest.controllerData = controllerData;

  auto pwItem = stmd.Construct(this->hwManager);
  BOOST_REQUIRE( pwItem );
  BOOST_CHECK_EQUAL( pwItem->getId(), id );
  auto stm = std::dynamic_pointer_cast<Lineside::ServoTurnoutMotor>(pwItem);
  BOOST_REQUIRE( stm );

  // Call the onActivate method
  pwItem->OnActivate();
  
  BOOST_CHECK_EQUAL( stm->GetState(), Lineside::TurnoutState::Straight );
  auto pwmChannel = this->hwManager->pwmChannelProvider->channels.at(controllerData);
  BOOST_CHECK_EQUAL( pwmChannel->Get(), straight );
}

BOOST_AUTO_TEST_CASE(SetStateAndStateChange)
{
  const unsigned int notifySrcId = 1235;
  std::shared_ptr<NotifyTarget> nt = std::make_shared<NotifyTarget>();
  
  const Lineside::ItemId id(10);
  const unsigned int straight = 10;
  const unsigned int curved = 113;
  const std::string controller = "MockPWMController";
  const std::string controllerData = "07";
  
  Lineside::ServoTurnoutMotorData stmd;
  stmd.id = id;
  stmd.straight = straight;
  stmd.curved = curved;
  stmd.pwmChannelRequest.controller = this->hwManager->PWMChannelProviderId;
  stmd.pwmChannelRequest.controllerData = controllerData;

  auto pwItem = stmd.Construct(this->hwManager);
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
  auto pwmChannel = this->hwManager->pwmChannelProvider->channels.at(controllerData);
  BOOST_CHECK_EQUAL( stm->GetState(), Lineside::TurnoutState::Straight );
  BOOST_CHECK_EQUAL( pwmChannel->Get(), straight );
  
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
  BOOST_CHECK_EQUAL( pwmChannel->Get(), straight );
  BOOST_CHECK(!pwItem->HaveStateChange());
}

BOOST_AUTO_TEST_SUITE_END()
