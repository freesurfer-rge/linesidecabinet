#include <functional>
#include <string>
#include <sstream>

#include <boost/test/unit_test.hpp>

#include "tendril/registrar.hpp"


std::function<bool(const Tendril::KeyException&)> GetKeyExceptionChecker(std::string expectedKeyName) {
  return [=](const Tendril::KeyException& ke) {
    std::stringstream s;
    s << "Expected key: " << expectedKeyName << std::endl;
    s << "  Actual key: " << ke.keyName << std::endl;
    BOOST_TEST_INFO(s.str());
    return expectedKeyName == ke.keyName;
  };
}


BOOST_AUTO_TEST_SUITE( Registrar )

BOOST_AUTO_TEST_CASE( StoreRetrieveOne )
{
  Tendril::Registrar<int> reg;

  auto target = std::make_shared<int>(1);
  BOOST_CHECK_EQUAL( target.use_count(), 1 );
  
  reg.Register( "One", target );
  BOOST_CHECK_EQUAL( target.use_count(), 2 );

  auto res = reg.Retrieve( "One" );
  BOOST_CHECK_EQUAL( target.use_count(), 3 );
  BOOST_CHECK_EQUAL( res.get(), target.get() );
}

BOOST_AUTO_TEST_CASE( NoDoubleStore )
{
  Tendril::Registrar<int> reg;

  reg.Register( "One", std::make_shared<int>(1) );
  BOOST_CHECK_EXCEPTION( reg.Register( "One", std::make_shared<int>(2) ),
			 Tendril::DuplicateKeyException,
			 GetKeyExceptionChecker("One") );
}

BOOST_AUTO_TEST_CASE( KeyNotRegistered )
{
  Tendril::Registrar<int> reg;

  BOOST_CHECK_EXCEPTION( reg.Retrieve("Two"),
			 Tendril::KeyNotFoundException,
			 GetKeyExceptionChecker("Two") );
}

BOOST_AUTO_TEST_SUITE_END()
