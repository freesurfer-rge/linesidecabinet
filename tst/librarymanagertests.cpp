#include <boost/test/unit_test.hpp>

#include "exceptionmessagecheck.hpp"

#include "pigpiod/librarymanager.hpp"

BOOST_AUTO_TEST_SUITE( LibraryManager )

BOOST_AUTO_TEST_CASE( Smoke )
{
  auto lm = Lineside::PiGPIOd::LibraryManager::CreateLibraryManager();
  BOOST_CHECK_EQUAL( lm.use_count(), 1 );
}

BOOST_AUTO_TEST_CASE( NoDoubleInitialise )
{
  auto lm = Lineside::PiGPIOd::LibraryManager::CreateLibraryManager();
  BOOST_CHECK_EQUAL( lm.use_count(), 1 );

  std::string msg("CreateLibraryManager: Already initialised");
  BOOST_CHECK_EXCEPTION( Lineside::PiGPIOd::LibraryManager::CreateLibraryManager(),
			 std::logic_error,
			 GetExceptionMessageChecker<std::logic_error>(msg) );
}

BOOST_AUTO_TEST_SUITE_END()
