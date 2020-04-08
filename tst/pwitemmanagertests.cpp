#include <boost/test/unit_test.hpp>

#include "multiaspectsignalheaddata.hpp"
#include "multiaspectsignalhead.hpp"


#include "utility.hpp"
#include "pwitemmanager.hpp"

#include "mockmanagerfixture.hpp"

#include "exceptionmessagecheck.hpp"

// ======================================

const std::string redData = "07";
const std::string greenData = "08";

static void AddAspect( Lineside::MultiAspectSignalHeadData& mashd,
		const std::string controller,
		const Lineside::SignalAspect a,
		const std::string data ) {
  Lineside::DeviceRequestData req;
  req.controller = controller;
  req.controllerData = data;

  mashd.aspectRequests[a] = req;
}

static std::shared_ptr<Lineside::MultiAspectSignalHeadData> MakeTwoAspect( const Lineside::ItemId id,
									   const std::string controller ) {
  auto mashd = std::make_shared<Lineside::MultiAspectSignalHeadData>();

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

  {
    Lineside::PWItemManager im(this->hwManager, this->swManager);

    // Create the MASH
    im.CreatePWItems( itemList );
    
    // The MASH should be showing a Red aspect
    BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(redData)->Get(), true );
    BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(greenData)->Get(), false );
    
    // Check we can get the MASH
    auto resWeak = im.GetPWItemModelById( id );
    LOCK_OR_THROW( res, resWeak );
    BOOST_REQUIRE( res );
    BOOST_CHECK_EQUAL( res->getId(), id );
    auto resMASH = std::dynamic_pointer_cast<Lineside::MultiAspectSignalHead>( res );
    BOOST_REQUIRE( resMASH );
  }

  // After destruct, both pins should be off
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(redData)->Get(), false );
  BOOST_CHECK_EQUAL( this->hwManager->bopProvider->pins.at(greenData)->Get(), false );
}

BOOST_AUTO_TEST_SUITE_END()
