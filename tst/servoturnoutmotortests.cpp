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
  stmd.pwmChannelRequest.controller = controller;
  stmd.pwmChannelRequest.controllerData = controllerData;

  auto pwItem = stmd.Construct(this->hwManager);
  BOOST_REQUIRE( pwItem );
  auto stm = std::dynamic_pointer_cast<Lineside::ServoTurnoutMotor>(pwItem);
  BOOST_REQUIRE( stm );
  BOOST_REQUIRE_GT( stm.use_count(), 0 );

  BOOST_CHECK_EQUAL( stm->getState(), Lineside::TurnoutState::Straight );
}

BOOST_AUTO_TEST_SUITE_END()
