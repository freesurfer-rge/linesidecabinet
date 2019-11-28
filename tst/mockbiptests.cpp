#include <thread>
#include <chrono>

#include <boost/test/unit_test.hpp>

#include "mocks/mockbip.hpp"

BOOST_AUTO_TEST_SUITE(MockBIPValidation)

BOOST_AUTO_TEST_CASE(GetAndSet)
{
  MockBIP mb;

  BOOST_CHECK_EQUAL( mb.Get(), false );
  mb.Set(true);
  BOOST_CHECK_EQUAL( mb.Get(), true );
  mb.Set(false);
  BOOST_CHECK_EQUAL( mb.Get(), false );
}

BOOST_AUTO_TEST_CASE(WaitAndNotify, *boost::unit_test::timeout(5) )
{
  MockBIP mb;

  BOOST_CHECK_EQUAL( mb.Get(), false );
  
  auto notifyDelay = std::chrono::seconds(2);

  auto start = std::chrono::system_clock::now();

  // Spin of thread which will notify us after a set time
  MockBIP* mbp = &mb;
  std::thread notifyThread( [notifyDelay,mbp]() {
			      std::this_thread::sleep_for(notifyDelay);
			      mbp->Set(true);
			    } );
  notifyThread.detach();

  // Wait on the notification
  BOOST_CHECK_EQUAL( mb.Get(), false );
  bool res = mb.Wait();
  auto stop = std::chrono::system_clock::now();

  // Check that we got the right result
  BOOST_CHECK_EQUAL( res, true );
  // Check there was a delay on the notification
  BOOST_CHECK( (stop-start) >= notifyDelay );
}

BOOST_AUTO_TEST_SUITE_END()
