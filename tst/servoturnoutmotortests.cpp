#include <boost/test/unit_test.hpp>

#include "servoturnoutmotordata.hpp"
#include "servoturnoutmotor.hpp"


BOOST_AUTO_TEST_SUITE(ServoTurnoutMotor)

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
}

BOOST_AUTO_TEST_SUITE_END()
