#include <boost/test/unit_test.hpp>

#include "pigpiodpp/pimanager.hpp"
#include "pigpiodpp/piboparray.hpp"

BOOST_AUTO_TEST_SUITE( PiBOPArray )

BOOST_AUTO_TEST_CASE( Smoke )
{
  auto pm = PiGPIOdpp::PiManager::CreatePiManager();

  std::vector<unsigned int> pinIds { 4, 10, 11 };
  PiGPIOdpp::PiBOPArray pba(pm, pinIds);

  BOOST_CHECK_EQUAL( pba.getPi(), pm->getId() );
  pba.Set(2, true); // i.e. pin 11 which is at index of 2 in pinIds
  BOOST_CHECK_NO_THROW( pba.Update() );
}

BOOST_AUTO_TEST_SUITE_END()
