#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include <sstream>

#include "lineside/signalaspect.hpp"

char const* aspectNames[] = { "Red", "Yellow1", "Yellow2", "Green" };
Lineside::SignalAspect aspects[] = { Lineside::SignalAspect::Red,
				     Lineside::SignalAspect::Yellow1,
				     Lineside::SignalAspect::Yellow2,
				     Lineside::SignalAspect::Green };

auto nameToAspectZip = boost::unit_test::data::make(aspectNames)
  ^ boost::unit_test::data::make(aspects);

BOOST_AUTO_TEST_SUITE( SignalAspect )

BOOST_DATA_TEST_CASE( ToString, nameToAspectZip, name, aspect )
{
  BOOST_CHECK_EQUAL( name, Lineside::ToString(aspect) );
}

BOOST_DATA_TEST_CASE( StreamInsertion, nameToAspectZip, name, aspect )
{
  std::stringstream res;
  res << aspect;
  BOOST_CHECK_EQUAL( res.str(), name );
}

BOOST_DATA_TEST_CASE( Parse, nameToAspectZip, name, aspect )
{
  BOOST_CHECK_EQUAL( aspect, Lineside::Parse<Lineside::SignalAspect>(name) );
}

BOOST_AUTO_TEST_SUITE_END()
