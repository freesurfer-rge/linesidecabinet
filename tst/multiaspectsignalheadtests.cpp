#include <boost/test/unit_test.hpp>

#include "multiaspectsignalheaddata.hpp"
#include "multiaspectsignalhead.hpp"

#include "mockhardwaremanagerfixture.hpp"

BOOST_FIXTURE_TEST_SUITE(MultiAspectSignalHead, MockHardwareManagerFixture)

BOOST_AUTO_TEST_CASE(ConstructTwoAspect)
{
  const Lineside::ItemId id(11);
  const std::string controller = this->hwManager->BOPProviderId;
  const std::string redData = "07";
  const std::string greenData = "08";

  Lineside::DeviceRequestData redRequest;
  redRequest.controller = controller;
  redRequest.controllerData = redData;

  Lineside::DeviceRequestData greenRequest;
  greenRequest.controller = controller;
  greenRequest.controllerData = greenData;

  Lineside::MultiAspectSignalHeadData mashd;
  mashd.id = id;
  mashd.aspectRequests[Lineside::SignalAspect::Red] = redRequest;
  mashd.aspectRequests[Lineside::SignalAspect::Green] = greenRequest;

  auto res = mashd.Construct( this->hwManager );
  BOOST_REQUIRE( res );
  BOOST_CHECK_EQUAL( res->getId(), id );
  auto resMASH = std::dynamic_pointer_cast<Lineside::MultiAspectSignalHead>(res);
  BOOST_REQUIRE( resMASH );

  // Ensure we have got the right number of output pins assigned
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.size(), 2 );

  // Check that the right pins were assigned
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.count(redData), 1 );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.count(greenData), 1 );
}

BOOST_AUTO_TEST_CASE(ConstructThreeAspect)
{
  BOOST_FAIL("Not yet implemented");
}

BOOST_AUTO_TEST_CASE(ConstructFourAspect)
{
  BOOST_FAIL("Not yet implemented");
}

BOOST_AUTO_TEST_CASE(ConstructTwoAspectWithOneFeather)
{
  BOOST_FAIL("Not yet implemented");
}

BOOST_AUTO_TEST_CASE(ConstructTwoAspectWithTwoFeathers)
{
  BOOST_FAIL("Not yet implemented");
}

BOOST_AUTO_TEST_SUITE_END()
