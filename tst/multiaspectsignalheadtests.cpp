#include <boost/test/unit_test.hpp>

#include "multiaspectsignalheaddata.hpp"
#include "multiaspectsignalhead.hpp"

#include "mockhardwaremanagerfixture.hpp"

// =====================================

const std::string redData = "07";
const std::string greenData = "08";
const std::string yellow1Data = "11";
const std::string yellow2Data = "13";

void AddAspect( Lineside::MultiAspectSignalHeadData& mashd,
		const std::string controller,
		const Lineside::SignalAspect a,
		const std::string data ) {
  Lineside::DeviceRequestData req;
  req.controller = controller;
  req.controllerData = data;

  mashd.aspectRequests[a] = req;
}

Lineside::MultiAspectSignalHeadData MakeTwoAspect( const Lineside::ItemId id,
						   const std::string controller ) {
  Lineside::MultiAspectSignalHeadData mashd;

  mashd.id = id;
  AddAspect( mashd, controller, Lineside::SignalAspect::Red, redData );
  AddAspect( mashd, controller, Lineside::SignalAspect::Green, greenData );

  return mashd;
}

// =====================================

BOOST_FIXTURE_TEST_SUITE(MultiAspectSignalHead, MockHardwareManagerFixture)

BOOST_AUTO_TEST_CASE(ConstructTwoAspect)
{
  const Lineside::ItemId id(11);

  auto mashd = MakeTwoAspect( id, this->hwManager->BOPProviderId ); 

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
