#include <boost/test/unit_test.hpp>

#include "utility.hpp"

#include "mocks/mockbopprovider.hpp"
#include "exceptionmessagecheck.hpp"

BOOST_AUTO_TEST_SUITE(MockBOPProviderValidation)

BOOST_AUTO_TEST_CASE(ConstructOne)
{
  MockBOPProvider mbb;
  BOOST_CHECK_EQUAL( mbb.pins.size(), 0 );

  const std::string channelId = "01";
  const std::map<std::string,std::string> settings;

  auto sbop = mbb.GetHardware(channelId, settings);
  BOOST_CHECK_EQUAL( mbb.pins.size(), 1 );
  auto sharedFromProvider = mbb.pins.at(channelId);

  BOOST_CHECK_EQUAL( sbop.get(), sharedFromProvider.get() );
}

BOOST_AUTO_TEST_CASE(ConstructTwo)
{
  MockBOPProvider mbb;
  BOOST_CHECK_EQUAL( mbb.pins.size(), 0 );

  const std::string ch01 = "01";
  const std::string ch02 = "012";
  const std::map<std::string,std::string> settings;

  auto sbop1 = mbb.GetHardware(ch01, settings);
  auto sbop2 = mbb.GetHardware(ch02, settings);

  BOOST_CHECK_EQUAL( mbb.pins.size(), 2 );
  BOOST_CHECK_NE( sbop1.get(), sbop2.get() );
}

BOOST_AUTO_TEST_CASE(NoDoubleRequest)
{
  MockBOPProvider mbb;
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
