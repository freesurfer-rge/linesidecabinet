#include <boost/test/unit_test.hpp>

#include "pigpiodpp/gpioedge.hpp"

#ifdef PIGPIODPP_HAVE_PIGPIO
#include <pigpiod_if2.h>
#else
#define RISING_EDGE  0
#define FALLING_EDGE 1
#define EITHER_EDGE  2
#endif

BOOST_AUTO_TEST_SUITE( GPIOEdge )

BOOST_AUTO_TEST_CASE( CheckValues )
{
  // Don't have the stream operators set up
  BOOST_CHECK_EQUAL( static_cast<int>(PiGPIOdpp::GPIOEdge::Rising), RISING_EDGE );
  BOOST_CHECK_EQUAL( static_cast<int>(PiGPIOdpp::GPIOEdge::Falling), FALLING_EDGE );
  BOOST_CHECK_EQUAL( static_cast<int>(PiGPIOdpp::GPIOEdge::Either), EITHER_EDGE );
}

BOOST_AUTO_TEST_SUITE_END()
