#include <boost/test/unit_test.hpp>

#include "multiaspectsignalheaddata.hpp"
#include "multiaspectsignalhead.hpp"

#include "mockhardwaremanagerfixture.hpp"

// =====================================

const std::string redData = "07";
const std::string greenData = "08";
const std::string yellow1Data = "11";
const std::string yellow2Data = "13";

const std::string feather1Data = "15";
const std::string feather2Data = "19";

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

Lineside::MultiAspectSignalHeadData MakeThreeAspect( const Lineside::ItemId id,
						     const std::string controller ) {
  Lineside::MultiAspectSignalHeadData mashd;

  mashd.id = id;
  AddAspect( mashd, controller, Lineside::SignalAspect::Red, redData );
  AddAspect( mashd, controller, Lineside::SignalAspect::Yellow1, yellow1Data );
  AddAspect( mashd, controller, Lineside::SignalAspect::Green, greenData );

  return mashd;
}

Lineside::MultiAspectSignalHeadData MakeFourAspect( const Lineside::ItemId id,
						    const std::string controller ) {
  Lineside::MultiAspectSignalHeadData mashd;

  mashd.id = id;
  AddAspect( mashd, controller, Lineside::SignalAspect::Red, redData );
  AddAspect( mashd, controller, Lineside::SignalAspect::Yellow1, yellow1Data );
  AddAspect( mashd, controller, Lineside::SignalAspect::Yellow2, yellow2Data );
  AddAspect( mashd, controller, Lineside::SignalAspect::Green, greenData );

  return mashd;
}

void AddFeather( Lineside::MultiAspectSignalHeadData& mashd,
		 const unsigned int featherId,
		 const std::string controller,
		 const std::string data ) {
  Lineside::DeviceRequestData req;
  req.controller = controller;
  req.controllerData = data;

  mashd.featherRequests[featherId] = req;;
}
		 

Lineside::MultiAspectSignalHeadData MakeTwoAspectOneFeather( const Lineside::ItemId id,
							     const std::string controller ) {
  auto mashd = MakeTwoAspect(id, controller);
  AddFeather(mashd, 1, controller, feather1Data);

  return mashd;
}

Lineside::MultiAspectSignalHeadData MakeTwoAspectTwoFeather( const Lineside::ItemId id,
							     const std::string controller ) {
  auto mashd = MakeTwoAspect(id, controller);
  AddFeather(mashd, 1, controller, feather1Data);
  AddFeather(mashd, 2, controller, feather2Data);

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
  const Lineside::ItemId id(12);

  auto mashd = MakeThreeAspect( id, this->hwManager->BOPProviderId );
  
  auto res = mashd.Construct( this->hwManager );
  BOOST_REQUIRE( res );
  BOOST_CHECK_EQUAL( res->getId(), id );
  auto resMASH = std::dynamic_pointer_cast<Lineside::MultiAspectSignalHead>(res);
  BOOST_REQUIRE( resMASH );

  // Ensure we have got the right number of output pins assigned
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.size(), 3 );

  // Check that the right pins were assigned
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.count(redData), 1 );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.count(yellow1Data), 1 );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.count(greenData), 1 );
}

BOOST_AUTO_TEST_CASE(ConstructFourAspect)
{
  const Lineside::ItemId id(12);
  
  auto mashd = MakeFourAspect( id, this->hwManager->BOPProviderId );
  
  auto res = mashd.Construct( this->hwManager );
  BOOST_REQUIRE( res );
  BOOST_CHECK_EQUAL( res->getId(), id );
  auto resMASH = std::dynamic_pointer_cast<Lineside::MultiAspectSignalHead>(res);
  BOOST_REQUIRE( resMASH );

  // Ensure we have got the right number of output pins assigned
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.size(), 4 );

  // Check that the right pins were assigned
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.count(redData), 1 );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.count(yellow1Data), 1 );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.count(yellow2Data), 1 );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.count(greenData), 1 );
}

BOOST_AUTO_TEST_CASE(ConstructTwoAspectWithOneFeather)
{
  const Lineside::ItemId id(16);

  auto mashd = MakeTwoAspectOneFeather( id, this->hwManager->BOPProviderId ); 

  auto res = mashd.Construct( this->hwManager );
  BOOST_REQUIRE( res );
  BOOST_CHECK_EQUAL( res->getId(), id );
  auto resMASH = std::dynamic_pointer_cast<Lineside::MultiAspectSignalHead>(res);
  BOOST_REQUIRE( resMASH );

  // Ensure we have got the right number of output pins assigned
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.size(), 3 );

  // Check that the right pins were assigned
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.count(redData), 1 );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.count(greenData), 1 );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.count(feather1Data), 1);
}

BOOST_AUTO_TEST_CASE(ConstructTwoAspectWithTwoFeathers)
{
  const Lineside::ItemId id(19);

  auto mashd = MakeTwoAspectTwoFeather( id, this->hwManager->BOPProviderId ); 

  auto res = mashd.Construct( this->hwManager );
  BOOST_REQUIRE( res );
  BOOST_CHECK_EQUAL( res->getId(), id );
  auto resMASH = std::dynamic_pointer_cast<Lineside::MultiAspectSignalHead>(res);
  BOOST_REQUIRE( resMASH );

  // Ensure we have got the right number of output pins assigned
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.size(), 4 );

  // Check that the right pins were assigned
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.count(redData), 1 );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.count(greenData), 1 );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.count(feather1Data), 1);
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.count(feather2Data), 1);
}

BOOST_AUTO_TEST_CASE(TwoAspectSetStateThrowsOnBadAspect)
{
  BOOST_FAIL("Not yet implemented");
}

BOOST_AUTO_TEST_CASE(ThreeAspectSetStateThrowsOnBadAspect)
{
  BOOST_FAIL("Not yet implemented");
}

BOOST_AUTO_TEST_CASE(TwoAspectSetStateThrowsOnBadFeather)
{
  BOOST_FAIL("Not yet implemented");
}

BOOST_AUTO_TEST_CASE(TwoAspectOneFeatherSetStateThrowsOnBadFeather)
{
  BOOST_FAIL("Not yet implemented");
}

BOOST_AUTO_TEST_SUITE_END()
