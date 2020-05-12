#include <boost/test/unit_test.hpp>

#include "exceptionmessagecheck.hpp"

#include "pigpiod/pigpiodexceptions.hpp"
#include "pigpiod/gpioprovider.hpp"

BOOST_AUTO_TEST_SUITE( GPIOProvider )

BOOST_AUTO_TEST_CASE( Smoke )
{
  auto pm = Lineside::PiGPIOd::PiManager::CreatePiManager();

  Lineside::PiGPIOd::GPIOProvider provider(pm);

  BOOST_CHECK_EQUAL(pm.use_count(), 2);
}

BOOST_AUTO_TEST_SUITE_END()
