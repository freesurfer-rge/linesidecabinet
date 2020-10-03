#include <boost/test/unit_test.hpp>

#include "pigpiodpp/piavailable.hpp"

BOOST_AUTO_TEST_SUITE( PiAvailable )

BOOST_AUTO_TEST_CASE( Smoke )
{
#ifdef PIGPIODPP_HAVE_PIGPIO
  BOOST_CHECK_EQUAL( PiGPIOdpp::piAvailable, true );
#else
  BOOST_CHECK_EQUAL( PiGPIOdpp::piAvailable, false );
#endif
}

BOOST_AUTO_TEST_SUITE_END()
