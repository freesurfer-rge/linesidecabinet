#include <boost/test/unit_test.hpp>
#include <boost/predef.h>

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
  Lineside::DeviceRequestData req;
  req.controller = controller;
  req.controllerData = data;

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
  auto mashd = MakeTwoAspect( id, this->hwManager->BOPProviderId );

  std::vector<std::shared_ptr<Lineside::PWItemData>> itemList;
  itemList.push_back(mashd);

  Lineside::PWItemManager im(this->hwManager, this->swManager);
  
  // Create the MASH
  im.CreatePWItems( itemList );
  
  // The MASH should be showing a Red aspect
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(redData)->Get(), true );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(greenData)->Get(), false );
  
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
  const std::string controller = "MockPWMController";
  const std::string controllerData = "07";

  auto stmd = std::make_shared<Lineside::ServoTurnoutMotorData>();
  stmd->id = id;
  stmd->straight = straight;
  stmd->curved = curved;
  stmd->pwmChannelRequest.controller = this->hwManager->PWMChannelProviderId;
  stmd->pwmChannelRequest.controllerData = controllerData;

  std::vector<std::shared_ptr<Lineside::PWItemData>> itemList;
  itemList.push_back(stmd);

  // Create the PWItemManager
  Lineside::PWItemManager im(this->hwManager, this->swManager);

  // Create the items
  im.CreatePWItems(itemList);

  // Check the servo was set to straight
  auto pwmChannel = this->hwManager->pwmChannelProvider->channels.at(controllerData);
  BOOST_CHECK_EQUAL( pwmChannel->Get(), straight );

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
  auto mashd = MakeTwoAspect( id, this->hwManager->BOPProviderId );

  // Make some STM data
  const unsigned int straight = 10;
  const unsigned int curved = 113;
  const std::string controller = "MockPWMController";
  const std::string controllerData = "07";
  
  auto stmd = std::make_shared<Lineside::ServoTurnoutMotorData>();
  stmd->id = id;
  stmd->straight = straight;
  stmd->curved = curved;
  stmd->pwmChannelRequest.controller = this->hwManager->PWMChannelProviderId;
  stmd->pwmChannelRequest.controllerData = controllerData;

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
