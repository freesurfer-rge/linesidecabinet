#include <boost/test/unit_test.hpp>

#include <sstream>

#include "lineside/multiaspectsignalheaddata.hpp"
#include "lineside/linesideexceptions.hpp"

#include "exceptionmessagecheck.hpp"

BOOST_AUTO_TEST_SUITE(MultiAspectSignalHeadData)

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
