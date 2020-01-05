#include <boost/test/unit_test.hpp>

#include <sstream>

#include "multiaspectsignalheaddata.hpp"
#include "linesideexceptions.hpp"

#include "exceptionmessagecheck.hpp"

BOOST_AUTO_TEST_SUITE(MultiAspectSignalHeadData)

BOOST_AUTO_TEST_CASE(NoRedAspect)
{
  Lineside::MultiAspectSignalHeadData mashd;

  std::stringstream msg;
  msg << "Key 'Red' not found";
  BOOST_CHECK_EXCEPTION( mashd.CheckData(),
			 Lineside::KeyNotFoundException,
			 GetExceptionMessageChecker<Lineside::KeyNotFoundException>( msg.str() ) );
}

BOOST_AUTO_TEST_CASE(NoGreenAspect)
{
  Lineside::MultiAspectSignalHeadData mashd;

  mashd.aspectRequests[Lineside::SignalAspect::Red] = Lineside::DeviceRequestData();

  std::stringstream msg;
  msg << "Key 'Green' not found";
  BOOST_CHECK_EXCEPTION( mashd.CheckData(),
			 Lineside::KeyNotFoundException,
			 GetExceptionMessageChecker<Lineside::KeyNotFoundException>( msg.str() ) );
}

BOOST_AUTO_TEST_CASE(Yellow2AspectButNoYellow1)
{
  Lineside::MultiAspectSignalHeadData mashd;

  mashd.aspectRequests[Lineside::SignalAspect::Red] = Lineside::DeviceRequestData();
  mashd.aspectRequests[Lineside::SignalAspect::Green] = Lineside::DeviceRequestData();
  mashd.aspectRequests[Lineside::SignalAspect::Yellow2] = Lineside::DeviceRequestData();

  std::stringstream msg;
  msg << "Key 'Yellow2' not found";
  BOOST_CHECK_EXCEPTION( mashd.CheckData(),
			 Lineside::KeyNotFoundException,
			 GetExceptionMessageChecker<Lineside::KeyNotFoundException>( msg.str() ) );
}

BOOST_AUTO_TEST_SUITE_END()
