#include <set>

#include <boost/test/unit_test.hpp>

#include "multiaspectsignalheaddata.hpp"
#include "multiaspectsignalhead.hpp"

#include "mockhardwaremanagerfixture.hpp"

#include "exceptionmessagecheck.hpp"

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

BOOST_AUTO_TEST_CASE(TwoAspectSetState)
{
  const Lineside::ItemId id(11);
  
  auto mashd = MakeTwoAspect( id, this->hwManager->BOPProviderId ); 
  
  auto res = mashd.Construct( this->hwManager );
  BOOST_REQUIRE( res );
  BOOST_CHECK_EQUAL( res->getId(), id );
  auto resMASH = std::dynamic_pointer_cast<Lineside::MultiAspectSignalHead>(res);
  BOOST_REQUIRE( resMASH );

  auto allowedStates = std::set<Lineside::SignalState> { Lineside::SignalState::Red,
							 Lineside::SignalState::Green };
  auto allowedFlash = std::set<Lineside::SignalFlash> { Lineside::SignalFlash::Steady,
							Lineside::SignalFlash::Flashing };
  const unsigned int feather = 0;
  for( auto itState=allowedStates.begin();
       itState!=allowedStates.end();
       ++itState ) {
    for( auto itFlash=allowedFlash.begin();
	 itFlash!=allowedFlash.end();
	 ++itFlash ) {
      BOOST_CHECK_NO_THROW( resMASH->SetState( *itState, *itFlash, feather ) );
    }
  }
}

BOOST_AUTO_TEST_CASE(ThreeAspectSetState)
{
  const Lineside::ItemId id(11);
  
  auto mashd = MakeThreeAspect( id, this->hwManager->BOPProviderId ); 
  
  auto res = mashd.Construct( this->hwManager );
  BOOST_REQUIRE( res );
  BOOST_CHECK_EQUAL( res->getId(), id );
  auto resMASH = std::dynamic_pointer_cast<Lineside::MultiAspectSignalHead>(res);
  BOOST_REQUIRE( resMASH );

  auto allowedStates = std::set<Lineside::SignalState> { Lineside::SignalState::Red,
							 Lineside::SignalState::Yellow,
							 Lineside::SignalState::Green };
  auto allowedFlash = std::set<Lineside::SignalFlash> { Lineside::SignalFlash::Steady,
							Lineside::SignalFlash::Flashing };
  const unsigned int feather = 0;
  for( auto itState=allowedStates.begin();
       itState!=allowedStates.end();
       ++itState ) {
    for( auto itFlash=allowedFlash.begin();
	 itFlash!=allowedFlash.end();
	 ++itFlash ) {
      BOOST_CHECK_NO_THROW( resMASH->SetState( *itState, *itFlash, feather ) );
    }
  }
}

BOOST_AUTO_TEST_CASE(FourAspectSetState)
{
  const Lineside::ItemId id(11);
  
  auto mashd = MakeFourAspect( id, this->hwManager->BOPProviderId ); 
  
  auto res = mashd.Construct( this->hwManager );
  BOOST_REQUIRE( res );
  BOOST_CHECK_EQUAL( res->getId(), id );
  auto resMASH = std::dynamic_pointer_cast<Lineside::MultiAspectSignalHead>(res);
  BOOST_REQUIRE( resMASH );

  auto allowedStates = std::set<Lineside::SignalState> { Lineside::SignalState::Red,
							 Lineside::SignalState::Yellow,
							 Lineside::SignalState::DoubleYellow,
							 Lineside::SignalState::Green };
  auto allowedFlash = std::set<Lineside::SignalFlash> { Lineside::SignalFlash::Steady,
							Lineside::SignalFlash::Flashing };
  const unsigned int feather = 0;
  for( auto itState=allowedStates.begin();
       itState!=allowedStates.end();
       ++itState ) {
    for( auto itFlash=allowedFlash.begin();
	 itFlash!=allowedFlash.end();
	 ++itFlash ) {
      BOOST_CHECK_NO_THROW( resMASH->SetState( *itState, *itFlash, feather ) );
    }
  }
}

BOOST_AUTO_TEST_CASE(TwoAspectSetStateWithTwoFeathers)
{
  const Lineside::ItemId id(11);
  
  auto mashd = MakeTwoAspectTwoFeather( id, this->hwManager->BOPProviderId ); 
  
  auto res = mashd.Construct( this->hwManager );
  BOOST_REQUIRE( res );
  BOOST_CHECK_EQUAL( res->getId(), id );
  auto resMASH = std::dynamic_pointer_cast<Lineside::MultiAspectSignalHead>(res);
  BOOST_REQUIRE( resMASH );

  auto allowedStates = std::set<Lineside::SignalState> { Lineside::SignalState::Red,
							 Lineside::SignalState::Green };
  auto allowedFlash = std::set<Lineside::SignalFlash> { Lineside::SignalFlash::Steady,
							Lineside::SignalFlash::Flashing };
  auto allowedFeather = std::set<unsigned int> { 0, 1, 2 };
  
  for( auto itState=allowedStates.begin();
       itState!=allowedStates.end();
       ++itState ) {
    for( auto itFlash=allowedFlash.begin();
	 itFlash!=allowedFlash.end();
	 ++itFlash ) {
      for( auto itFeather=allowedFeather.begin();
	   itFeather!=allowedFeather.end();
	   ++itFeather ) {
	BOOST_CHECK_NO_THROW( resMASH->SetState( *itState, *itFlash, *itFeather ) );
      }
    }
  }
}

BOOST_AUTO_TEST_CASE(TwoAspectSetStateThrowsOnBadAspect)
{
  const Lineside::ItemId id(11);
  
  auto mashd = MakeTwoAspect( id, this->hwManager->BOPProviderId ); 
  
  auto res = mashd.Construct( this->hwManager );
  BOOST_REQUIRE( res );
  BOOST_CHECK_EQUAL( res->getId(), id );
  auto resMASH = std::dynamic_pointer_cast<Lineside::MultiAspectSignalHead>(res);
  BOOST_REQUIRE( resMASH );

  auto forbiddenStates = std::set<Lineside::SignalState> { Lineside::SignalState::Yellow,
							   Lineside::SignalState::DoubleYellow };
  auto checkFlash = std::set<Lineside::SignalFlash> { Lineside::SignalFlash::Steady,
						      Lineside::SignalFlash::Flashing };
  const unsigned int feather = 0;
  for( auto itState=forbiddenStates.begin();
       itState!=forbiddenStates.end();
       ++itState ) {
    for( auto itFlash=checkFlash.begin();
	 itFlash!=checkFlash.end();
	 ++itFlash ) {
      std::stringstream msg;
      msg << "Invalid state for " << id << ".";
      msg << " State was: {"
	  << *itState << "," << *itFlash << "," << feather << "}";
      BOOST_CHECK_EXCEPTION( resMASH->SetState( *itState, *itFlash, feather ),
			     Lineside::InvalidStateException,
			     GetExceptionMessageChecker<Lineside::InvalidStateException>( msg.str() ));
    }
  }
}
    
BOOST_AUTO_TEST_CASE(ThreeAspectSetStateThrowsOnBadAspect)
{
  const Lineside::ItemId id(16);
  
  auto mashd = MakeThreeAspect( id, this->hwManager->BOPProviderId ); 
  
  auto res = mashd.Construct( this->hwManager );
  BOOST_REQUIRE( res );
  BOOST_CHECK_EQUAL( res->getId(), id );
  auto resMASH = std::dynamic_pointer_cast<Lineside::MultiAspectSignalHead>(res);
  BOOST_REQUIRE( resMASH );

  auto forbiddenStates = std::set<Lineside::SignalState> { Lineside::SignalState::DoubleYellow };
  auto checkFlash = std::set<Lineside::SignalFlash> { Lineside::SignalFlash::Steady,
						      Lineside::SignalFlash::Flashing };
  const unsigned int feather = 0;
  for( auto itState=forbiddenStates.begin();
       itState!=forbiddenStates.end();
       ++itState ) {
    for( auto itFlash=checkFlash.begin();
	 itFlash!=checkFlash.end();
	 ++itFlash ) {
      std::stringstream msg;
      msg << "Invalid state for " << id << ".";
      msg << " State was: {"
	  << *itState << "," << *itFlash << "," << feather << "}";
      BOOST_CHECK_EXCEPTION( resMASH->SetState( *itState, *itFlash, feather ),
			     Lineside::InvalidStateException,
			     GetExceptionMessageChecker<Lineside::InvalidStateException>( msg.str() ));
    }
  }
}

BOOST_AUTO_TEST_CASE(TwoAspectSetStateThrowsOnBadFeather)
{
  const Lineside::ItemId id(15);
  
  auto mashd = MakeTwoAspect( id, this->hwManager->BOPProviderId ); 
  
  auto res = mashd.Construct( this->hwManager );
  BOOST_REQUIRE( res );
  BOOST_CHECK_EQUAL( res->getId(), id );
  auto resMASH = std::dynamic_pointer_cast<Lineside::MultiAspectSignalHead>(res);
  BOOST_REQUIRE( resMASH );

  auto allowedStates = std::set<Lineside::SignalState> { Lineside::SignalState::Red,
							 Lineside::SignalState::Green };
  auto allowedFlash = std::set<Lineside::SignalFlash> { Lineside::SignalFlash::Steady,
							Lineside::SignalFlash::Flashing };
  const unsigned int badFeather = 1;
  for( auto itState=allowedStates.begin();
       itState!=allowedStates.end();
       ++itState ) {
    for( auto itFlash=allowedFlash.begin();
	 itFlash!=allowedFlash.end();
	 ++itFlash ) {
      std::stringstream msg;
      msg << "Invalid state for " << id << ".";
      msg << " State was: {"
	  << *itState << "," << *itFlash << "," << badFeather << "}";
      BOOST_CHECK_EXCEPTION( resMASH->SetState( *itState, *itFlash, badFeather ),
			     Lineside::InvalidStateException,
			     GetExceptionMessageChecker<Lineside::InvalidStateException>( msg.str() ));
    }
  }
}

BOOST_AUTO_TEST_CASE(TwoAspectOneFeatherSetStateThrowsOnBadFeather)
{
  const Lineside::ItemId id(85);
  
  auto mashd = MakeTwoAspectOneFeather( id, this->hwManager->BOPProviderId ); 
  
  auto res = mashd.Construct( this->hwManager );
  BOOST_REQUIRE( res );
  BOOST_CHECK_EQUAL( res->getId(), id );
  auto resMASH = std::dynamic_pointer_cast<Lineside::MultiAspectSignalHead>(res);
  BOOST_REQUIRE( resMASH );
  
  auto allowedStates = std::set<Lineside::SignalState> { Lineside::SignalState::Red,
							 Lineside::SignalState::Green };
  auto allowedFlash = std::set<Lineside::SignalFlash> { Lineside::SignalFlash::Steady,
							Lineside::SignalFlash::Flashing };
  const unsigned int badFeather = 2;
  for( auto itState=allowedStates.begin();
       itState!=allowedStates.end();
       ++itState ) {
    for( auto itFlash=allowedFlash.begin();
	 itFlash!=allowedFlash.end();
	 ++itFlash ) {
      std::stringstream msg;
      msg << "Invalid state for " << id << ".";
      msg << " State was: {"
	  << *itState << "," << *itFlash << "," << badFeather << "}";
      BOOST_CHECK_EXCEPTION( resMASH->SetState( *itState, *itFlash, badFeather ),
			     Lineside::InvalidStateException,
			     GetExceptionMessageChecker<Lineside::InvalidStateException>( msg.str() ));
    }
  }
}


BOOST_AUTO_TEST_CASE(ShowsRedOnActivateTwoAspect)
{
  const Lineside::ItemId id(11);
  
  auto mashd = MakeTwoAspect( id, this->hwManager->BOPProviderId ); 
  
  auto res = mashd.Construct( this->hwManager );
  BOOST_REQUIRE( res );
  BOOST_CHECK_EQUAL( res->getId(), id );
  auto resMASH = std::dynamic_pointer_cast<Lineside::MultiAspectSignalHead>(res);
  BOOST_REQUIRE( resMASH );

  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(redData)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(greenData)->Get(), false );

  // Activate the signal head
  res->OnActivate();

  // Check we're now showing Red
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(redData)->Get(), true );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(greenData)->Get(), false );
}

BOOST_AUTO_TEST_CASE(ShowsRedOnActivateFourAspect)
{
  const Lineside::ItemId id(11);
  
  auto mashd = MakeFourAspect( id, this->hwManager->BOPProviderId ); 
  
  auto res = mashd.Construct( this->hwManager );
  BOOST_REQUIRE( res );
  BOOST_CHECK_EQUAL( res->getId(), id );
  auto resMASH = std::dynamic_pointer_cast<Lineside::MultiAspectSignalHead>(res);
  BOOST_REQUIRE( resMASH );

  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(redData)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(yellow1Data)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(yellow2Data)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(greenData)->Get(), false );

  // Activate the signal head
  res->OnActivate();

  // Check we're now showing Red
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(redData)->Get(), true );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(yellow1Data)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(yellow2Data)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(greenData)->Get(), false );
}

BOOST_AUTO_TEST_CASE(ShowsRedOnActivateTwoAspectWithFeather)
{
  const Lineside::ItemId id(11);
  
  auto mashd = MakeTwoAspectOneFeather( id, this->hwManager->BOPProviderId ); 
  
  auto res = mashd.Construct( this->hwManager );
  BOOST_REQUIRE( res );
  BOOST_CHECK_EQUAL( res->getId(), id );
  auto resMASH = std::dynamic_pointer_cast<Lineside::MultiAspectSignalHead>(res);
  BOOST_REQUIRE( resMASH );

  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(redData)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(greenData)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(feather1Data)->Get(), false );

  // Activate the signal head
  res->OnActivate();

  // Check we're now showing Red
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(redData)->Get(), true );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(greenData)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(feather1Data)->Get(), false );
}

BOOST_AUTO_TEST_CASE(OnRunTwoAspectSteady)
{
  const Lineside::ItemId id(11);
  
  auto mashd = MakeTwoAspect( id, this->hwManager->BOPProviderId ); 
  
  auto res = mashd.Construct( this->hwManager );
  BOOST_REQUIRE( res );
  BOOST_CHECK_EQUAL( res->getId(), id );
  auto resMASH = std::dynamic_pointer_cast<Lineside::MultiAspectSignalHead>(res);
  BOOST_REQUIRE( resMASH );

  resMASH->OnActivate();
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(redData)->Get(), true );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(greenData)->Get(), false );

  // Set to Green
  resMASH->SetState( Lineside::SignalState::Green, Lineside::SignalFlash::Steady, 0 );
  BOOST_CHECK( resMASH->HaveStateChange() );
  auto sleepTime = resMASH->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(redData)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(greenData)->Get(), true );

  // Setting to Green again should give no change
  BOOST_CHECK( !resMASH->HaveStateChange() );
  resMASH->SetState( Lineside::SignalState::Green, Lineside::SignalFlash::Steady, 0 );
  BOOST_CHECK( !resMASH->HaveStateChange() );
  sleepTime = resMASH->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(redData)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(greenData)->Get(), true );
  
  // Set to Red
  resMASH->SetState( Lineside::SignalState::Red, Lineside::SignalFlash::Steady, 0 );
  BOOST_CHECK( resMASH->HaveStateChange() );
  sleepTime = resMASH->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(redData)->Get(), true );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(greenData)->Get(), false );
}

BOOST_AUTO_TEST_CASE(OnRunThreeAspectSteady)
{
  const Lineside::ItemId id(11);
  
  auto mashd = MakeThreeAspect( id, this->hwManager->BOPProviderId ); 
  
  auto res = mashd.Construct( this->hwManager );
  BOOST_REQUIRE( res );
  BOOST_CHECK_EQUAL( res->getId(), id );
  auto resMASH = std::dynamic_pointer_cast<Lineside::MultiAspectSignalHead>(res);
  BOOST_REQUIRE( resMASH );

  resMASH->OnActivate();
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(redData)->Get(), true );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(yellow1Data)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(greenData)->Get(), false );

  // Set to Green
  resMASH->SetState( Lineside::SignalState::Green, Lineside::SignalFlash::Steady, 0 );
  BOOST_CHECK( resMASH->HaveStateChange() );
  auto sleepTime = resMASH->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(redData)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(yellow1Data)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(greenData)->Get(), true );
  BOOST_CHECK( !resMASH->HaveStateChange() );

  // Set to Yellow
  resMASH->SetState( Lineside::SignalState::Yellow, Lineside::SignalFlash::Steady, 0 );
  BOOST_CHECK( resMASH->HaveStateChange() );
  sleepTime = resMASH->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(redData)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(yellow1Data)->Get(), true );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(greenData)->Get(), false );
  BOOST_CHECK( !resMASH->HaveStateChange() );
  
  // Set to Red
  resMASH->SetState( Lineside::SignalState::Red, Lineside::SignalFlash::Steady, 0 );
  BOOST_CHECK( resMASH->HaveStateChange() );
  sleepTime = resMASH->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(redData)->Get(), true );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(yellow1Data)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(greenData)->Get(), false );
  BOOST_CHECK( !resMASH->HaveStateChange() );
}

BOOST_AUTO_TEST_CASE(OnRunFourAspectSteady)
{
  const Lineside::ItemId id(11);
  
  auto mashd = MakeFourAspect( id, this->hwManager->BOPProviderId ); 
  
  auto res = mashd.Construct( this->hwManager );
  BOOST_REQUIRE( res );
  BOOST_CHECK_EQUAL( res->getId(), id );
  auto resMASH = std::dynamic_pointer_cast<Lineside::MultiAspectSignalHead>(res);
  BOOST_REQUIRE( resMASH );

  resMASH->OnActivate();
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(redData)->Get(), true );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(yellow1Data)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(yellow2Data)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(greenData)->Get(), false );

  // Set to Green
  resMASH->SetState( Lineside::SignalState::Green, Lineside::SignalFlash::Steady, 0 );
  BOOST_CHECK( resMASH->HaveStateChange() );
  auto sleepTime = resMASH->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(redData)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(yellow1Data)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(yellow2Data)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(greenData)->Get(), true );
  BOOST_CHECK( !resMASH->HaveStateChange() );
  
  // Set to Double Yellow
  resMASH->SetState( Lineside::SignalState::DoubleYellow, Lineside::SignalFlash::Steady, 0 );
  BOOST_CHECK( resMASH->HaveStateChange() );
  sleepTime = resMASH->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(redData)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(yellow1Data)->Get(), true );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(yellow2Data)->Get(), true );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(greenData)->Get(), false );
  BOOST_CHECK( !resMASH->HaveStateChange() );
  
  // Set to Yellow
  resMASH->SetState( Lineside::SignalState::Yellow, Lineside::SignalFlash::Steady, 0 );
  BOOST_CHECK( resMASH->HaveStateChange() );
  sleepTime = resMASH->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(redData)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(yellow1Data)->Get(), true );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(yellow2Data)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(greenData)->Get(), false );
  BOOST_CHECK( !resMASH->HaveStateChange() );
  
  // Set to Red
  resMASH->SetState( Lineside::SignalState::Red, Lineside::SignalFlash::Steady, 0 );
  BOOST_CHECK( resMASH->HaveStateChange() );
  sleepTime = resMASH->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(redData)->Get(), true );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(yellow1Data)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(yellow2Data)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(greenData)->Get(), false );
  BOOST_CHECK( !resMASH->HaveStateChange() );
}

BOOST_AUTO_TEST_CASE( OnRunTwoAspectFlashing )
{
  const Lineside::ItemId id(11);
  
  auto mashd = MakeTwoAspect( id, this->hwManager->BOPProviderId ); 
  
  auto res = mashd.Construct( this->hwManager );
  BOOST_REQUIRE( res );
  BOOST_CHECK_EQUAL( res->getId(), id );
  auto resMASH = std::dynamic_pointer_cast<Lineside::MultiAspectSignalHead>(res);
  BOOST_REQUIRE( resMASH );

  resMASH->OnActivate();
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(redData)->Get(), true );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(greenData)->Get(), false );

  // Set to Flashing Green
  resMASH->SetState( Lineside::SignalState::Green, Lineside::SignalFlash::Flashing, 0 );
  BOOST_CHECK( resMASH->HaveStateChange() );

  // First call should set to on
  auto sleepTime = resMASH->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(redData)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(greenData)->Get(), true );
  BOOST_CHECK( !resMASH->HaveStateChange() );

  // Call again and it should be off
  sleepTime = resMASH->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(redData)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(greenData)->Get(), false );
  BOOST_CHECK( !resMASH->HaveStateChange() );

  // And call again, it should be back on
  sleepTime = resMASH->OnRun();
  BOOST_CHECK( sleepTime == std::chrono::milliseconds(500) );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(redData)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(greenData)->Get(), true );
  BOOST_CHECK( !resMASH->HaveStateChange() );
}

BOOST_AUTO_TEST_SUITE_END()
