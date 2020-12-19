#include <boost/test/unit_test.hpp>

#include <sstream>

#include "lineside/directdrivemashdata.hpp"
#include "lineside/linesideexceptions.hpp"

#include "exceptionmessagecheck.hpp"

BOOST_AUTO_TEST_SUITE(DirectDriveMASHData)

BOOST_AUTO_TEST_CASE(NoRedAspect)
{
  Lineside::DirectDriveMASHData mashd;
  mashd.id = 15;

  std::string msg = "Configuration problem for 00:00:00:0f - Red aspect missing";
  BOOST_CHECK_EXCEPTION( mashd.CheckData(),
			 Lineside::BadPWItemDataException,
			 GetExceptionMessageChecker<Lineside::BadPWItemDataException>( msg ) );
}

BOOST_AUTO_TEST_CASE(NoGreenAspect)
{
  Lineside::DirectDriveMASHData mashd;
  mashd.id = 14;

  mashd.aspectRequests[Lineside::SignalAspect::Red] = Tendril::HardwareRequestData();

  std::string msg = "Configuration problem for 00:00:00:0e - Green aspect missing";
  BOOST_CHECK_EXCEPTION( mashd.CheckData(),
			 Lineside::BadPWItemDataException,
			 GetExceptionMessageChecker<Lineside::BadPWItemDataException>( msg ) );
}

BOOST_AUTO_TEST_CASE(Yellow2AspectButNoYellow1)
{
  Lineside::DirectDriveMASHData mashd;
  mashd.id = 13;

  mashd.aspectRequests[Lineside::SignalAspect::Red] = Tendril::HardwareRequestData();
  mashd.aspectRequests[Lineside::SignalAspect::Green] = Tendril::HardwareRequestData();
  mashd.aspectRequests[Lineside::SignalAspect::Yellow2] = Tendril::HardwareRequestData();

  std::string msg("Configuration problem for 00:00:00:0d - Have Yellow2 aspect but no Yellow1");
  BOOST_CHECK_EXCEPTION( mashd.CheckData(),
			 Lineside::BadPWItemDataException,
			 GetExceptionMessageChecker<Lineside::BadPWItemDataException>( msg ) );
}

BOOST_AUTO_TEST_CASE(TwoAspectOK)
{
  Lineside::DirectDriveMASHData mashd;

  mashd.aspectRequests[Lineside::SignalAspect::Red] = Tendril::HardwareRequestData();
  mashd.aspectRequests[Lineside::SignalAspect::Green] = Tendril::HardwareRequestData();

  BOOST_CHECK_NO_THROW( mashd.CheckData() );
}

BOOST_AUTO_TEST_CASE(ThreeAspectOK)
{
  Lineside::DirectDriveMASHData mashd;

  mashd.aspectRequests[Lineside::SignalAspect::Red] = Tendril::HardwareRequestData();
  mashd.aspectRequests[Lineside::SignalAspect::Green] = Tendril::HardwareRequestData();
  mashd.aspectRequests[Lineside::SignalAspect::Yellow1] = Tendril::HardwareRequestData();

  BOOST_CHECK_NO_THROW( mashd.CheckData() );
}

BOOST_AUTO_TEST_CASE(FourAspectOK)
{
  Lineside::DirectDriveMASHData mashd;

  mashd.aspectRequests[Lineside::SignalAspect::Red] = Tendril::HardwareRequestData();
  mashd.aspectRequests[Lineside::SignalAspect::Green] = Tendril::HardwareRequestData();
  mashd.aspectRequests[Lineside::SignalAspect::Yellow1] = Tendril::HardwareRequestData();
  mashd.aspectRequests[Lineside::SignalAspect::Yellow2] = Tendril::HardwareRequestData();

  BOOST_CHECK_NO_THROW( mashd.CheckData() );
}

BOOST_AUTO_TEST_CASE(FeathersZeroDefined)
{
  Lineside::DirectDriveMASHData mashd;
  mashd.id = 255;
  mashd.aspectRequests[Lineside::SignalAspect::Red] = Tendril::HardwareRequestData();
  mashd.aspectRequests[Lineside::SignalAspect::Green] = Tendril::HardwareRequestData();

  mashd.featherRequests[0] = Tendril::HardwareRequestData();
  std::string msg = "Configuration problem for 00:00:00:ff - Feather '0' defined";
  BOOST_CHECK_EXCEPTION( mashd.CheckData(),
			 Lineside::BadPWItemDataException,
			 GetExceptionMessageChecker<Lineside::BadPWItemDataException>( msg ) );
}

BOOST_AUTO_TEST_CASE(FeathersNonSequential)
{
  Lineside::DirectDriveMASHData mashd;
  mashd.id = 255;
  mashd.aspectRequests[Lineside::SignalAspect::Red] = Tendril::HardwareRequestData();
  mashd.aspectRequests[Lineside::SignalAspect::Green] = Tendril::HardwareRequestData();

  mashd.featherRequests[2] = Tendril::HardwareRequestData();
  std::string msg = "Configuration problem for 00:00:00:ff - Feathers are not sequential from one";
  BOOST_CHECK_EXCEPTION( mashd.CheckData(),
			 Lineside::BadPWItemDataException,
			 GetExceptionMessageChecker<Lineside::BadPWItemDataException>( msg ) );
}

BOOST_AUTO_TEST_CASE(SingleFeatherOK)
{
  Lineside::DirectDriveMASHData mashd;
  mashd.id = 255;
  mashd.aspectRequests[Lineside::SignalAspect::Red] = Tendril::HardwareRequestData();
  mashd.aspectRequests[Lineside::SignalAspect::Green] = Tendril::HardwareRequestData();

  mashd.featherRequests[1] = Tendril::HardwareRequestData();
  BOOST_CHECK_NO_THROW( mashd.CheckData() );
}

BOOST_AUTO_TEST_CASE(TwoFeathersOK)
{
  Lineside::DirectDriveMASHData mashd;
  mashd.id = 255;
  mashd.aspectRequests[Lineside::SignalAspect::Red] = Tendril::HardwareRequestData();
  mashd.aspectRequests[Lineside::SignalAspect::Green] = Tendril::HardwareRequestData();

  mashd.featherRequests[1] = Tendril::HardwareRequestData();
  mashd.featherRequests[2] = Tendril::HardwareRequestData();
  BOOST_CHECK_NO_THROW( mashd.CheckData() );
}

BOOST_AUTO_TEST_SUITE_END()
