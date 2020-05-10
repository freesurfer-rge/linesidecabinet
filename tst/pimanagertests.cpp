#include <boost/test/unit_test.hpp>

#include "exceptionmessagecheck.hpp"

#include "pigpiod/pimanager.hpp"

BOOST_AUTO_TEST_SUITE( PiManager )

BOOST_AUTO_TEST_CASE( Smoke )
{
  auto lm = Lineside::PiGPIOd::PiManager::CreatePiManager();
  BOOST_CHECK_EQUAL( lm.use_count(), 1 );
}

BOOST_AUTO_TEST_CASE( NoDoubleInitialise )
{
  auto lm = Lineside::PiGPIOd::PiManager::CreatePiManager();
  BOOST_CHECK_EQUAL( lm.use_count(), 1 );

  std::string msg("CreatePiManager: Already initialised");
  BOOST_CHECK_EXCEPTION( Lineside::PiGPIOd::PiManager::CreatePiManager(),
			 std::logic_error,
			 GetExceptionMessageChecker<std::logic_error>(msg) );
}

BOOST_AUTO_TEST_SUITE_END()
