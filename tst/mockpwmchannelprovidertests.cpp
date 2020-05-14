#include <boost/test/unit_test.hpp>

#include "utility.hpp"

#include "mocks/mockpwmchannelprovider.hpp"
#include "exceptionmessagecheck.hpp"

BOOST_AUTO_TEST_SUITE(MockPWMChannelProviderValidation)

BOOST_AUTO_TEST_CASE(ConstructOne)
{
  MockPWMChannelProvider mcp;
  
  const std::string channelId = "01";
  const std::map<std::string,std::string> settings;

  auto spc = mcp.GetHardware(channelId, settings);
  BOOST_CHECK_EQUAL( mcp.channels.size(), 1 );
  auto sharedFromProvider = mcp.channels.at(channelId);
  
  BOOST_CHECK_EQUAL( spc.get(), sharedFromProvider.get() );
}

BOOST_AUTO_TEST_CASE(ConstructTwo)
{
   MockPWMChannelProvider mcp;

   const std::string ch01 = "01";
   const std::string ch02 = "02";
   const std::map<std::string,std::string> settings;

   auto spc1 = mcp.GetHardware(ch01, settings);
   auto spc2 = mcp.GetHardware(ch02, settings);

   BOOST_CHECK_EQUAL( mcp.channels.size(), 2 );
   BOOST_CHECK_NE( spc1.get(), spc2.get() );
}

BOOST_AUTO_TEST_CASE(NoDoubleRequest)
{
  MockPWMChannelProvider mcp;

  const std::string chId = "01";
  const std::map<std::string,std::string> settings;

  auto spc = mcp.GetHardware(chId, settings);

  std::string msg("Key '01' already present");
  BOOST_CHECK_EXCEPTION( mcp.GetHardware(chId, settings),
			 Lineside::DuplicateKeyException,
			 GetExceptionMessageChecker<Lineside::DuplicateKeyException>( msg ) );
}

BOOST_AUTO_TEST_SUITE_END()
