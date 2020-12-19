#include <boost/test/unit_test.hpp>
#include <boost/predef.h>

#include "tendril/mocks/utilities.hpp"
#include "tendril/mocks/mockhardwareprovider.hpp"
#include "tendril/mocks/mockbop.hpp"
#include "tendril/mocks/mockpwmchannel.hpp"

#include "lineside/linesideexceptions.hpp"

#include "lineside/directdrivemashdata.hpp"
#include "lineside/directdrivemash.hpp"
#include "lineside/servoturnoutmotordata.hpp"
#include "lineside/servoturnoutmotor.hpp"


#include "lineside/pwitemmanager.hpp"

#include "mockmanagerfixture.hpp"

#include "exceptionmessagecheck.hpp"

// ======================================

const std::string redData = "07";
const std::string greenData = "08";

static void AddAspect( Lineside::DirectDriveMASHData& mashd,
		       const std::string controller,
		       const Lineside::SignalAspect a,
		       const std::string data ) {
  Tendril::HardwareRequestData req;
  req.providerName = controller;
  req.idOnProvider = data;

  mashd.aspectRequests[a] = req;
}

static std::shared_ptr<Lineside::DirectDriveMASHData> MakeTwoAspect( const Lineside::ItemId id,
								     const std::string controller ) {
  auto mashd = std::make_shared<Lineside::DirectDriveMASHData>();

  mashd->id = id;
  AddAspect( *mashd, controller, Lineside::SignalAspect::Red, redData );
  AddAspect( *mashd, controller, Lineside::SignalAspect::Green, greenData );

  return mashd;
}

// ======================================

BOOST_FIXTURE_TEST_SUITE(PWItemManager, MockManagerFixture)

BOOST_AUTO_TEST_CASE(SingleMASH)
{
  // Make the MASH data
  const Lineside::ItemId id(131);
  auto mashd = MakeTwoAspect( id, Tendril::Mocks::BOPProviderId );

  std::vector<std::shared_ptr<Lineside::PWItemData>> itemList;
  itemList.push_back(mashd);

  Lineside::PWItemManager im(this->hwManager, this->swManager);
  
  // Create the MASH
  im.CreatePWItems( itemList );
  
  // The MASH should be showing a Red aspect
  
  auto mockProvider = this->hwManager->bopProviderRegistrar.Retrieve(Tendril::Mocks::BOPProviderId);
  auto mockbopProvider = std::dynamic_pointer_cast<Tendril::Mocks::MockHardwareProvider<Tendril::BinaryOutputPin, Tendril::Mocks::MockBOP>>(mockProvider);
  BOOST_REQUIRE( mockbopProvider );
  BOOST_CHECK_EQUAL( mockbopProvider->hardware.at(redData)->lastLevel, true );
  BOOST_CHECK_EQUAL( mockbopProvider->hardware.at(greenData)->lastLevel, false );
  
  // Check we can get the MASH
  Lineside::PWItemModel& res = im.GetPWItemModelById(id);
  BOOST_CHECK_EQUAL( res.getId(), id );
#if defined(BOOST_COMP_GNUC)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-value"
#elif defined(BOOST_COMP_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-value"
#endif
  BOOST_CHECK_NO_THROW( dynamic_cast<Lineside::DirectDriveMASH&>(res) );
#if defined(BOOST_COMP_GNUC)
#pragma GCC diagnostic pop
#elif defined(BOOST_COMP_CLANG)
#pragma clang diagnostic pop
#endif
}

BOOST_AUTO_TEST_CASE(SingleSTM)
{
  const Lineside::ItemId id(10);
  const unsigned int straight = 10;
  const unsigned int curved = 113;
  const std::string controller = Tendril::Mocks::PWMCProviderId;
  const std::string idOnProvider = "07";

  auto stmd = std::make_shared<Lineside::ServoTurnoutMotorData>();
  stmd->id = id;
  stmd->straight = straight;
  stmd->curved = curved;
  stmd->pwmChannelRequest.providerName = Tendril::Mocks::PWMCProviderId;
  stmd->pwmChannelRequest.idOnProvider = idOnProvider;

  std::vector<std::shared_ptr<Lineside::PWItemData>> itemList;
  itemList.push_back(stmd);

  // Create the PWItemManager
  Lineside::PWItemManager im(this->hwManager, this->swManager);

  // Create the items
  im.CreatePWItems(itemList);

  // Check the servo was set to straight
  auto mockProvider = this->hwManager->pwmcProviderRegistrar.Retrieve(controller);
  auto mockpwmcProvider = std::dynamic_pointer_cast<Tendril::Mocks::MockHardwareProvider<Tendril::PWMChannel, Tendril::Mocks::MockPWMChannel>>(mockProvider);
  auto pwmChannel = mockpwmcProvider->hardware.at(idOnProvider);
  auto lastUpdate = pwmChannel->updates.back();
  BOOST_CHECK_EQUAL( lastUpdate.first, 0 );
  BOOST_CHECK_EQUAL( lastUpdate.second, straight );

  // Check we can get the STM
  Lineside::PWItemModel& res = im.GetPWItemModelById(id);
  BOOST_CHECK_EQUAL( res.getId(), id );
#if defined(BOOST_COMP_GNUC)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-value"
#elif defined(BOOST_COMP_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-value"
#endif
  BOOST_CHECK_NO_THROW( dynamic_cast<Lineside::ServoTurnoutMotor&>(res) );
#if defined(BOOST_COMP_GNUC)
#pragma GCC diagnostic pop
#elif defined(BOOST_COMP_CLANG)
#pragma clang diagnostic pop
#endif
}

BOOST_AUTO_TEST_CASE(DuplicateId)
{
   // Make the MASH data
  const Lineside::ItemId id(131);
  auto mashd = MakeTwoAspect( id, Tendril::Mocks::BOPProviderId );

  // Make some STM data
  const unsigned int straight = 10;
  const unsigned int curved = 113;
  const std::string controller = "MockPWMController";
  const std::string idOnProvider = "07";
  
  auto stmd = std::make_shared<Lineside::ServoTurnoutMotorData>();
  stmd->id = id;
  stmd->straight = straight;
  stmd->curved = curved;
  stmd->pwmChannelRequest.providerName = Tendril::Mocks::PWMCProviderId;
  stmd->pwmChannelRequest.idOnProvider = idOnProvider;

  std::vector<std::shared_ptr<Lineside::PWItemData>> itemList;
  itemList.push_back(mashd);
  itemList.push_back(stmd);

  // Create the PWItemManager
  Lineside::PWItemManager im(this->hwManager, this->swManager);

  std::string msg = "Key '00:00:00:83' already present";
  BOOST_CHECK_EXCEPTION( im.CreatePWItems( itemList ),
			 Lineside::DuplicateKeyException,
			 GetExceptionMessageChecker<Lineside::DuplicateKeyException>(msg) );
}

BOOST_AUTO_TEST_CASE(IdNotPresent)
{
  Lineside::PWItemManager im(this->hwManager, this->swManager);

  const Lineside::ItemId noSuchId(256);
  std::string msg = "Key '00:00:01:00' not found";
  BOOST_CHECK_EXCEPTION( im.GetPWItemModelById(noSuchId),
			 Lineside::KeyNotFoundException,
			 GetExceptionMessageChecker<Lineside::KeyNotFoundException>(msg) );
}

BOOST_AUTO_TEST_SUITE_END()
