#include <boost/test/unit_test.hpp>

#include "pigpiodpp/gpiopin.hpp"

BOOST_AUTO_TEST_SUITE( GPIOPin )

BOOST_AUTO_TEST_CASE( Smoke )
{
  auto pm = PiGPIOdpp::PiManager::CreatePiManager();

  const int pinId = 5;
  PiGPIOdpp::GPIOPin pin(pm, pinId);
  
  BOOST_CHECK_EQUAL( pin.getPi(), pm->getId() );
  BOOST_CHECK_EQUAL( pin.getPin(), pinId );
}

BOOST_AUTO_TEST_CASE( CallBackInvoked )
{
  const unsigned char pinId = 5;
  auto pm = PiGPIOdpp::PiManager::CreatePiManager();

  PiGPIOdpp::GPIOPin pin(pm, pinId);

  bool funcCalled = false;
  bool level = false;
  PiGPIOdpp::GPIOPin::CallBackFn f = [&funcCalled,&level](bool l) {
				       funcCalled = true;
				       level = l;
				     };

  pin.SetCallBack(PiGPIOdpp::GPIOEdge::Either, f);

  // Invoke to true
  pin.InvokeCallBack(pin.getPi(), pinId, 1, 0);
  BOOST_CHECK( funcCalled );
  BOOST_CHECK( level );

  // Invoke to false
  funcCalled = false;
  pin.InvokeCallBack(pin.getPi(), pinId, 0, 0);
  BOOST_CHECK( funcCalled );
  BOOST_CHECK( !level );
}

BOOST_AUTO_TEST_SUITE_END()
