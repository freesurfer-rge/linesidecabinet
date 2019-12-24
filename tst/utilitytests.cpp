#include <boost/test/unit_test.hpp>

#include "utility.hpp"

BOOST_AUTO_TEST_SUITE(Utility)

BOOST_AUTO_TEST_SUITE(Lock_Or_Throw)

BOOST_AUTO_TEST_CASE(Successful)
{
  const int anyInt = 10;
  auto myInt = std::make_shared<int>(anyInt);

  BOOST_CHECK( myInt );
  BOOST_CHECK_EQUAL( *myInt, anyInt );
  BOOST_CHECK_EQUAL( myInt.use_count(), 1 );

  auto wp = std::weak_ptr<int>(myInt);
  BOOST_CHECK_EQUAL( wp.use_count(), 1 );

  LOCK_OR_THROW( sp, wp );

  BOOST_CHECK_EQUAL( myInt.use_count(), 2 );
  BOOST_CHECK_EQUAL( wp.use_count(), 2 );
  BOOST_CHECK_EQUAL( *sp, *myInt );
  BOOST_CHECK_EQUAL( sp.get(), myInt.get() );
}

BOOST_AUTO_TEST_CASE(Failure)
{
  auto wp = std::weak_ptr<int>();
  BOOST_CHECK( wp.expired() );

  {
    const int anyInt = 10;
    auto myInt = std::make_shared<int>(anyInt);

    wp = myInt;
    BOOST_CHECK( !wp.expired() );
    BOOST_CHECK_EQUAL( wp.use_count(), 1 );
  }

  BOOST_CHECK( wp.expired() );

  BOOST_CHECK_EXCEPTION( LOCK_OR_THROW( sp, wp ),
			 Lineside::PointerLockFailureException,
			 [&](const Lineside::PointerLockFailureException& e) {
			   BOOST_CHECK_EQUAL( e.linenumber, 45 );
			   BOOST_CHECK_NE( e.filename.find("utilitytests.cpp"),
					   std::string::npos );

			   return true;
			 } );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
