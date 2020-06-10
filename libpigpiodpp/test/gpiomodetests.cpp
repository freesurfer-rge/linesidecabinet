#include <boost/test/unit_test.hpp>

#include "pigpiodpp/gpiomode.hpp"

#ifdef PIGPIODPP_HAVE_PIGPIO
#include <pigpiod_if2.h>
#else
#define PI_INPUT  0
#define PI_OUTPUT 1
#endif

BOOST_AUTO_TEST_SUITE( GPIOMode )

BOOST_AUTO_TEST_CASE( CheckValues )
{
  BOOST_CHECK_EQUAL( static_cast<int>(PiGPIOdpp::GPIOMode::Input), PI_INPUT );
  BOOST_CHECK_EQUAL( static_cast<int>(PiGPIOdpp::GPIOMode::Output), PI_OUTPUT );
}

BOOST_AUTO_TEST_SUITE_END()
