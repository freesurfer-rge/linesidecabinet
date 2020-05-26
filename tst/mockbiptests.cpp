#include <thread>
#include <chrono>

#include <boost/test/unit_test.hpp>

#include "mocks/mockbip.hpp"
#include "notifytarget.hpp"

/*
  These tests are more about validating the code in the abstract
  class BinaryOutputPin than the MockBIP itself.
 */


BOOST_AUTO_TEST_SUITE( Mocks )

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

BOOST_AUTO_TEST_CASE(NotifySingleTarget)
{
  MockBIP mb;

  const int srcId = 10;
  std::shared_ptr<NotifyTarget> nt(new NotifyTarget);
  BOOST_CHECK_EQUAL( nt->lastNotificationSource, 0 );
  BOOST_CHECK_EQUAL( nt->lastNotification, false );

  mb.RegisterListener( srcId, nt );

  mb.Set(true);
  BOOST_CHECK_EQUAL( nt->lastNotificationSource, srcId );
  BOOST_CHECK_EQUAL( nt->lastNotification, true );

  nt->lastNotificationSource = 0;

  mb.Set(false);
  BOOST_CHECK_EQUAL( nt->lastNotificationSource, srcId );
  BOOST_CHECK_EQUAL( nt->lastNotification, false );
}

BOOST_AUTO_TEST_CASE(NotifyTwoTargets)
{
  MockBIP mb;

  const int src1 = 10;
  const int src2 = src1+12;

  std::shared_ptr<NotifyTarget> nt1(new NotifyTarget);
  std::shared_ptr<NotifyTarget> nt2(new NotifyTarget);
  
  BOOST_CHECK_EQUAL( nt1->lastNotificationSource, 0 );
  BOOST_CHECK_EQUAL( nt1->lastNotification, false );
  BOOST_CHECK_EQUAL( nt2->lastNotificationSource, 0 );
  BOOST_CHECK_EQUAL( nt2->lastNotification, false );

  mb.RegisterListener( src1, nt1 );
  mb.RegisterListener( src2, nt2 );

  mb.Set(true);
  BOOST_CHECK_EQUAL( nt1->lastNotificationSource, src1 );
  BOOST_CHECK_EQUAL( nt1->lastNotification, true );
  BOOST_CHECK_EQUAL( nt2->lastNotificationSource, src2 );
  BOOST_CHECK_EQUAL( nt2->lastNotification, true );
  
  nt1->lastNotificationSource = 0;
  nt2->lastNotificationSource = 0;

  mb.Set(false);
  BOOST_CHECK_EQUAL( nt1->lastNotificationSource, src1 );
  BOOST_CHECK_EQUAL( nt1->lastNotification, false );
  BOOST_CHECK_EQUAL( nt2->lastNotificationSource, src2 );
  BOOST_CHECK_EQUAL( nt2->lastNotification, false );
}

BOOST_AUTO_TEST_CASE(ExpiredTargetHarmless)
{
  MockBIP mb;

  {
    const int srcId = 10;
    std::shared_ptr<NotifyTarget> nt(new NotifyTarget);

    mb.RegisterListener( srcId, nt );
    // nt Goes out of scope and we only took a weak_ptr
  }

  // Still should be OK
  BOOST_CHECK_NO_THROW(mb.Set(true));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
