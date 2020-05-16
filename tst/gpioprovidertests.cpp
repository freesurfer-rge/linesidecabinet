#include <boost/test/unit_test.hpp>

#include "exceptionmessagecheck.hpp"

#include "linesideexceptions.hpp"
#include "pigpiod/gpioprovider.hpp"

BOOST_AUTO_TEST_SUITE( GPIOProvider )

BOOST_AUTO_TEST_CASE( Smoke )
{
  auto pm = Lineside::PiGPIOd::PiManager::CreatePiManager();

  Lineside::PiGPIOd::GPIOProvider provider(pm);

  BOOST_CHECK_EQUAL(pm.use_count(), 2);
}

BOOST_AUTO_TEST_CASE( GetOneOutput )
{
  auto pm = Lineside::PiGPIOd::PiManager::CreatePiManager();

  Lineside::PiGPIOd::GPIOProvider provider(pm);

  auto pin = provider.GetGPOutput(5);

  // Should start with the pin in off state
  BOOST_CHECK_EQUAL( pin->Get(), false );
}

BOOST_AUTO_TEST_CASE( NoDoublePinId )
{
  const unsigned char pinId = 5;
  auto pm = Lineside::PiGPIOd::PiManager::CreatePiManager();

  Lineside::PiGPIOd::GPIOProvider provider(pm);

  auto pin = provider.GetGPOutput(pinId);

  std::string msg("Key '5' already present");
  BOOST_CHECK_EXCEPTION( provider.GetGPOutput(pinId),
			 Lineside::DuplicateKeyException,
			 GetExceptionMessageChecker<Lineside::DuplicateKeyException>(msg) );
}

BOOST_AUTO_TEST_SUITE_END()
