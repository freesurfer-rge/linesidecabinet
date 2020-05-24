#include <boost/test/unit_test.hpp>

#include "utility.hpp"

#include "mocks/mockbipprovider.hpp"
#include "exceptionmessagecheck.hpp"

BOOST_AUTO_TEST_SUITE(MockBIPProviderValidation)

BOOST_AUTO_TEST_CASE(ConstructOne)
{
  MockBIPProvider mbb;
  BOOST_CHECK_EQUAL( mbb.pins.size(), 0 );

  const std::string channelId = "01";
  const std::map<std::string,std::string> settings;

  auto bop = mbb.GetHardware(channelId, settings);
  BOOST_CHECK_EQUAL( mbb.pins.size(), 1 );
  auto fromProvider = mbb.pins.at(channelId);

  BOOST_CHECK_EQUAL( bop.get(), fromProvider );
}

BOOST_AUTO_TEST_CASE(ConstructTwo)
{
  MockBIPProvider mbb;
  BOOST_CHECK_EQUAL( mbb.pins.size(), 0 );

  const std::string ch01 = "01";
  const std::string ch02 = "012";
  const std::map<std::string,std::string> settings;

  auto bop1 = mbb.GetHardware(ch01, settings);
  auto bop2 = mbb.GetHardware(ch02, settings);

  BOOST_CHECK_EQUAL( mbb.pins.size(), 2 );
  BOOST_CHECK_NE( bop1.get(), bop2.get() );
}

BOOST_AUTO_TEST_CASE(NoDoubleRequest)
{
  MockBIPProvider mbb;
  BOOST_CHECK_EQUAL( mbb.pins.size(), 0 );
  
  const std::string chId = "01";
  const std::map<std::string,std::string> settings;

  auto spc = mbb.GetHardware(chId, settings);

  std::string msg("Key '01' already present");
  BOOST_CHECK_EXCEPTION( mbb.GetHardware(chId, settings),
			 Lineside::DuplicateKeyException,
			 GetExceptionMessageChecker<Lineside::DuplicateKeyException>(msg) );
}

BOOST_AUTO_TEST_SUITE_END()
