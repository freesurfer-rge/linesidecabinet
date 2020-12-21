#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include <sstream>

#include "pigpiodpp/gpiopull.hpp"

#ifdef PIGPIODPP_HAVE_PIGPIO
#include <pigpiod_if2.h>
#else
#define PI_PUD_OFF  0
#define PI_PUD_DOWN 1
#define PI_PUD_UP   2
#endif

// ==================

char const* pullNames[] = { "Off", "Down", "Up" };
PiGPIOdpp::GPIOPull pulls[] = { PiGPIOdpp::GPIOPull::Off,
				PiGPIOdpp::GPIOPull::Down,
				PiGPIOdpp::GPIOPull::Up };

auto nameToPullZip = boost::unit_test::data::make(pullNames)
  ^ boost::unit_test::data::make(pulls);

// ===================

BOOST_AUTO_TEST_SUITE( GPIOPull )

BOOST_AUTO_TEST_CASE( CheckValues )
{
  BOOST_CHECK_EQUAL( static_cast<int>(PiGPIOdpp::GPIOPull::Off), PI_PUD_OFF );
  BOOST_CHECK_EQUAL( static_cast<int>(PiGPIOdpp::GPIOPull::Down), PI_PUD_DOWN );
  BOOST_CHECK_EQUAL( static_cast<int>(PiGPIOdpp::GPIOPull::Up), PI_PUD_UP );
}

BOOST_DATA_TEST_CASE( ToString, nameToPullZip, name, pull )
{
  BOOST_CHECK_EQUAL( name, PiGPIOdpp::ToString(pull) );
}

BOOST_DATA_TEST_CASE( StreamInsertion, nameToPullZip, name, pull )
{
  std::stringstream res;
  res << pull;
  BOOST_CHECK_EQUAL( res.str(), name );
}

BOOST_DATA_TEST_CASE( Parse, nameToPullZip, name, pull )
{
  BOOST_CHECK_EQUAL( pull, PiGPIOdpp::Parse<PiGPIOdpp::GPIOPull>(name) );
}

BOOST_AUTO_TEST_CASE( BadParse )
{
  const std::string badString = "SomeRandomString";

  const std::string expected = "Could not parse 'SomeRandomString' to GPIOPull";
  BOOST_CHECK_EXCEPTION( PiGPIOdpp::Parse<PiGPIOdpp::GPIOPull>(badString),
			 std::invalid_argument,
			 [=](const std::invalid_argument& ia) {
			   BOOST_CHECK_EQUAL( expected, ia.what() );
			   return expected == ia.what();
			 });
}

BOOST_AUTO_TEST_SUITE_END()
