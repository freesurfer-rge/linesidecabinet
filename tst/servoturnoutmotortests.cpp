#include <boost/test/unit_test.hpp>

#include "servoturnoutmotordata.hpp"
#include "servoturnoutmotor.hpp"

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

  BOOST_CHECK_EQUAL( stm->getState(), Lineside::TurnoutState::Straight );
  auto pwmChannel = this->hwManager->pwmChannelProvider->channels.at(controllerData);
  BOOST_CHECK_EQUAL( pwmChannel->Get(), straight );
}

BOOST_AUTO_TEST_CASE(SetCurved)
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
  BOOST_REQUIRE_EQUAL( stm.use_count(), 2 );

  BOOST_FAIL("Need to implement the rest");
}

BOOST_AUTO_TEST_SUITE_END()
