#include <boost/test/unit_test.hpp>

#include "tendril/mocks/mocknotifiable.hpp"
#include "tendril/notifier.hpp"

BOOST_AUTO_TEST_SUITE( Notifier )

BOOST_AUTO_TEST_CASE( BasicNotification )
{
  auto target = std::make_shared<Tendril::Mocks::MockNotifiable<bool>>();

  Tendril::Notifier<bool> subject;

  subject.Register(target);

  subject.Notify(true);
  BOOST_CHECK_EQUAL( target->lastNotification, true );

  subject.Notify(false);
  BOOST_CHECK_EQUAL( target->lastNotification, false );
}

BOOST_AUTO_TEST_CASE( NotifyMultiple )
{
  const size_t nTargets = 10;
  std::vector<std::shared_ptr<Tendril::Mocks::MockNotifiable<bool>>> targets;
  for( size_t i=0; i<nTargets; i++ ) {
    targets.push_back(std::make_shared<Tendril::Mocks::MockNotifiable<bool>>());
  }

  Tendril::Notifier<bool> subject;

  for( auto& it: targets ) {
    subject.Register(it);
  }

  subject.Notify(true);
  for( auto& it: targets ) {
    BOOST_CHECK_EQUAL( it->lastNotification, true );
  }

  subject.Notify(false);
  for( auto& it: targets ) {
    BOOST_CHECK_EQUAL( it->lastNotification, false );
  }
}

BOOST_AUTO_TEST_CASE( CopeWithDeadTargets )
{
  const size_t nTargets = 10;
  std::vector<std::shared_ptr<Tendril::Mocks::MockNotifiable<bool>>> targets;
  for( size_t i=0; i<nTargets; i++ ) {
    targets.push_back(std::make_shared<Tendril::Mocks::MockNotifiable<bool>>());
  }

  Tendril::Notifier<bool> subject;

  for( auto& it: targets ) {
    subject.Register(it);
  }

  subject.Notify(true);
  for( auto& it: targets ) {
    BOOST_CHECK_EQUAL( it->lastNotification, true );
  }

  // Now delete some targets
  targets.erase(targets.begin() + 4);
  targets.erase(targets.begin());
  targets.pop_back();
  BOOST_REQUIRE_EQUAL( targets.size(), nTargets-3 );

  subject.Notify(false);
  for( auto& it: targets ) {
    BOOST_CHECK_EQUAL( it->lastNotification, false );
  }
}

BOOST_AUTO_TEST_SUITE_END()
