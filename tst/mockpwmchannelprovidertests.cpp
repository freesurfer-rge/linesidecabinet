#include <boost/test/unit_test.hpp>

#include "utility.hpp"

#include "mocks/mockpwmchannelprovider.hpp"
#include "exceptionmessagecheck.hpp"

BOOST_AUTO_TEST_SUITE( Mocks )

BOOST_AUTO_TEST_SUITE(MockPWMChannelProviderValidation)

BOOST_AUTO_TEST_CASE(ConstructOne)
{
  MockPWMChannelProvider mcp;
  
  const std::string channelId = "01";
  const std::map<std::string,std::string> settings;

  auto pc = mcp.GetHardware(channelId, settings);
  BOOST_CHECK_EQUAL( mcp.channels.size(), 1 );
  auto fromProvider = mcp.channels.at(channelId);
  
  BOOST_CHECK_EQUAL( pc.get(), fromProvider );
}

BOOST_AUTO_TEST_CASE(ConstructTwo)
{
   MockPWMChannelProvider mcp;

   const std::string ch01 = "01";
   const std::string ch02 = "02";
   const std::map<std::string,std::string> settings;

   auto pc1 = mcp.GetHardware(ch01, settings);
   auto pc2 = mcp.GetHardware(ch02, settings);

   BOOST_CHECK_EQUAL( mcp.channels.size(), 2 );
   BOOST_CHECK_NE( pc1.get(), pc2.get() );
}

BOOST_AUTO_TEST_CASE(NoDoubleRequest)
{
  MockPWMChannelProvider mcp;

  const std::string chId = "01";
  const std::map<std::string,std::string> settings;

  auto pc = mcp.GetHardware(chId, settings);

  std::string msg("Key '01' already present");
  BOOST_CHECK_EXCEPTION( mcp.GetHardware(chId, settings),
			 Lineside::DuplicateKeyException,
			 GetExceptionMessageChecker<Lineside::DuplicateKeyException>( msg ) );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
