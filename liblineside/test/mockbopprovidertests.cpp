#include <boost/test/unit_test.hpp>

#include "lineside/linesideexceptions.hpp"

#include "mocks/mockbopprovider.hpp"
#include "exceptionmessagecheck.hpp"

BOOST_AUTO_TEST_SUITE( Mocks )

BOOST_AUTO_TEST_SUITE(MockBOPProviderValidation)

BOOST_AUTO_TEST_CASE(ConstructOne)
{
  MockBOPProvider mbb;
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
  MockBOPProvider mbb;
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
  MockBOPProvider mbb;
  BOOST_CHECK_EQUAL( mbb.pins.size(), 0 );
  
  const std::string chId = "01";
  const std::map<std::string,std::string> settings;

  auto bop = mbb.GetHardware(chId, settings);

  std::string msg("Key '01' already present");
  BOOST_CHECK_EXCEPTION( mbb.GetHardware(chId, settings),
			 Lineside::DuplicateKeyException,
			 GetExceptionMessageChecker<Lineside::DuplicateKeyException>(msg) );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
