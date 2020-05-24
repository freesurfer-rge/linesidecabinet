#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include <sstream>

#include "pigpiod/gpiopull.hpp"

char const* pullNames[] = { "Off", "Down", "Up" };
Lineside::PiGPIOd::GPIOPull pulls[] = { Lineside::PiGPIOd::GPIOPull::Off,
					Lineside::PiGPIOd::GPIOPull::Down,
					Lineside::PiGPIOd::GPIOPull::Up };

auto nameToPullZip = boost::unit_test::data::make(pullNames)
  ^ boost::unit_test::data::make(pulls);

BOOST_AUTO_TEST_SUITE( GPIOPull )

BOOST_DATA_TEST_CASE( ToString, nameToPullZip, name, pull )
{
  BOOST_CHECK_EQUAL( name, Lineside::PiGPIOd::ToString(pull) );
}

BOOST_DATA_TEST_CASE( StreamInsertion, nameToPullZip, name, pull )
{
  std::stringstream res;
  res << pull;
  BOOST_CHECK_EQUAL( res.str(), name );
}

BOOST_DATA_TEST_CASE( Parse, nameToPullZip, name, pull )
{
  BOOST_CHECK_EQUAL( pull, Lineside::Parse<Lineside::PiGPIOd::GPIOPull>(name) );
}

BOOST_AUTO_TEST_SUITE_END()
