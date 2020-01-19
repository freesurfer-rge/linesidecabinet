#include <boost/test/unit_test.hpp>

#include <sstream>

#include "multiaspectsignalheaddata.hpp"
#include "linesideexceptions.hpp"
#include "utility.hpp"

#include "mockhardwaremanagerfixture.hpp"

#include "exceptionmessagecheck.hpp"

BOOST_FIXTURE_TEST_SUITE(MultiAspectSignalHeadData, MockHardwareManagerFixture)

BOOST_AUTO_TEST_SUITE(CheckData)

BOOST_AUTO_TEST_CASE(NoRedAspect)
{
  Lineside::MultiAspectSignalHeadData mashd;
  mashd.id = 15;

  std::string msg = "Configuration problem for 00:00:00:0f - Red aspect missing";
  BOOST_CHECK_EXCEPTION( mashd.CheckData(),
			 Lineside::BadPWItemDataException,
			 GetExceptionMessageChecker<Lineside::BadPWItemDataException>( msg ) );
}

BOOST_AUTO_TEST_CASE(NoGreenAspect)
{
  Lineside::MultiAspectSignalHeadData mashd;
  mashd.id = 14;

  mashd.aspectRequests[Lineside::SignalAspect::Red] = Lineside::DeviceRequestData();

  std::string msg = "Configuration problem for 00:00:00:0e - Green aspect missing";
  BOOST_CHECK_EXCEPTION( mashd.CheckData(),
			 Lineside::BadPWItemDataException,
			 GetExceptionMessageChecker<Lineside::BadPWItemDataException>( msg ) );
}

BOOST_AUTO_TEST_CASE(Yellow2AspectButNoYellow1)
{
  Lineside::MultiAspectSignalHeadData mashd;
  mashd.id = 13;

  mashd.aspectRequests[Lineside::SignalAspect::Red] = Lineside::DeviceRequestData();
  mashd.aspectRequests[Lineside::SignalAspect::Green] = Lineside::DeviceRequestData();
  mashd.aspectRequests[Lineside::SignalAspect::Yellow2] = Lineside::DeviceRequestData();

  std::string msg("Configuration problem for 00:00:00:0d - Have Yellow2 aspect but no Yellow1");
  BOOST_CHECK_EXCEPTION( mashd.CheckData(),
			 Lineside::BadPWItemDataException,
			 GetExceptionMessageChecker<Lineside::BadPWItemDataException>( msg ) );
}

BOOST_AUTO_TEST_CASE(TwoAspectOK)
{
  Lineside::MultiAspectSignalHeadData mashd;

  mashd.aspectRequests[Lineside::SignalAspect::Red] = Lineside::DeviceRequestData();
  mashd.aspectRequests[Lineside::SignalAspect::Green] = Lineside::DeviceRequestData();

  BOOST_CHECK_NO_THROW( mashd.CheckData() );
}

BOOST_AUTO_TEST_CASE(ThreeAspectOK)
{
  Lineside::MultiAspectSignalHeadData mashd;

  mashd.aspectRequests[Lineside::SignalAspect::Red] = Lineside::DeviceRequestData();
  mashd.aspectRequests[Lineside::SignalAspect::Green] = Lineside::DeviceRequestData();
  mashd.aspectRequests[Lineside::SignalAspect::Yellow1] = Lineside::DeviceRequestData();

  BOOST_CHECK_NO_THROW( mashd.CheckData() );
}

BOOST_AUTO_TEST_CASE(FourAspectOK)
{
  Lineside::MultiAspectSignalHeadData mashd;

  mashd.aspectRequests[Lineside::SignalAspect::Red] = Lineside::DeviceRequestData();
  mashd.aspectRequests[Lineside::SignalAspect::Green] = Lineside::DeviceRequestData();
  mashd.aspectRequests[Lineside::SignalAspect::Yellow1] = Lineside::DeviceRequestData();
  mashd.aspectRequests[Lineside::SignalAspect::Yellow2] = Lineside::DeviceRequestData();

  BOOST_CHECK_NO_THROW( mashd.CheckData() );
}

BOOST_AUTO_TEST_CASE(FeathersZeroDefined)
{
  Lineside::MultiAspectSignalHeadData mashd;
  mashd.id = 255;
  mashd.aspectRequests[Lineside::SignalAspect::Red] = Lineside::DeviceRequestData();
  mashd.aspectRequests[Lineside::SignalAspect::Green] = Lineside::DeviceRequestData();

  mashd.featherRequests[0] = Lineside::DeviceRequestData();
  std::string msg = "Configuration problem for 00:00:00:ff - Feather '0' defined";
  BOOST_CHECK_EXCEPTION( mashd.CheckData(),
			 Lineside::BadPWItemDataException,
			 GetExceptionMessageChecker<Lineside::BadPWItemDataException>( msg ) );
}

BOOST_AUTO_TEST_CASE(FeathersNonSequential)
{
  Lineside::MultiAspectSignalHeadData mashd;
  mashd.id = 255;
  mashd.aspectRequests[Lineside::SignalAspect::Red] = Lineside::DeviceRequestData();
  mashd.aspectRequests[Lineside::SignalAspect::Green] = Lineside::DeviceRequestData();

  mashd.featherRequests[2] = Lineside::DeviceRequestData();
  std::string msg = "Configuration problem for 00:00:00:ff - Feathers are not sequential from one";
  BOOST_CHECK_EXCEPTION( mashd.CheckData(),
			 Lineside::BadPWItemDataException,
			 GetExceptionMessageChecker<Lineside::BadPWItemDataException>( msg ) );
}

BOOST_AUTO_TEST_CASE(SingleFeatherOK)
{
  Lineside::MultiAspectSignalHeadData mashd;
  mashd.id = 255;
  mashd.aspectRequests[Lineside::SignalAspect::Red] = Lineside::DeviceRequestData();
  mashd.aspectRequests[Lineside::SignalAspect::Green] = Lineside::DeviceRequestData();

  mashd.featherRequests[1] = Lineside::DeviceRequestData();
  BOOST_CHECK_NO_THROW( mashd.CheckData() );
}

BOOST_AUTO_TEST_CASE(TwoFeathersOK)
{
  Lineside::MultiAspectSignalHeadData mashd;
  mashd.id = 255;
  mashd.aspectRequests[Lineside::SignalAspect::Red] = Lineside::DeviceRequestData();
  mashd.aspectRequests[Lineside::SignalAspect::Green] = Lineside::DeviceRequestData();

  mashd.featherRequests[1] = Lineside::DeviceRequestData();
  mashd.featherRequests[2] = Lineside::DeviceRequestData();
  BOOST_CHECK_NO_THROW( mashd.CheckData() );
}

BOOST_AUTO_TEST_SUITE_END()

// ================================================

BOOST_AUTO_TEST_SUITE(GenerateOutputStateMap)

BOOST_AUTO_TEST_CASE(TwoAspect)
{
  const std::string controller = "MockBOPController";
  const std::string redData = "07";
  const std::string greenData = "08";
  Lineside::MultiAspectSignalHeadData mashd;
  mashd.id = 255;

  Lineside::DeviceRequestData redRequest, greenRequest;
  redRequest.controller = this->hwManager->BOPProviderId;
  greenRequest.controller = this->hwManager->BOPProviderId;
  redRequest.controllerData = redData;
  greenRequest.controllerData = greenData;
  
  
  mashd.aspectRequests[Lineside::SignalAspect::Red] = redRequest;
  mashd.aspectRequests[Lineside::SignalAspect::Green] = greenRequest;

  auto res = mashd.GenerateOutputStateMap( this->hwManager );
  BOOST_CHECK_EQUAL( res.size(), 2 );

  // Check that the right states are present, and controlling the correct
  // number of lamps. Make these comparisons required so that we can
  // assume subsequent operations on the multimap will succeed
  BOOST_REQUIRE_EQUAL( res.count(Lineside::SignalState::Red), 1 );
  BOOST_REQUIRE_EQUAL( res.count(Lineside::SignalState::Green), 1 );

  // Since there's only one of each, we can use multimap::find
  auto redIt = res.find(Lineside::SignalState::Red);
  LOCK_OR_THROW( redPin, redIt->second );
  BOOST_CHECK_EQUAL( redPin, this->hwManager->bopProvider->pins.at(redData) );

  auto greenIt = res.find(Lineside::SignalState::Green);
  LOCK_OR_THROW( greenPin, greenIt->second );
  BOOST_CHECK_EQUAL( greenPin, this->hwManager->bopProvider->pins.at(greenData) );
}

BOOST_AUTO_TEST_CASE(ThreeAspect)
{
  BOOST_FAIL("Not yet implemented");
}

BOOST_AUTO_TEST_CASE(FourAspect)
{
  BOOST_FAIL("Not yet implemented");
}

BOOST_AUTO_TEST_SUITE_END()
  
BOOST_AUTO_TEST_SUITE_END()
