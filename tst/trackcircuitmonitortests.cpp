#include <boost/test/unit_test.hpp>

#include "trackcircuitmonitordata.hpp"
#include "trackcircuitmonitor.hpp"

#include "mockmanagerfixture.hpp"

// ======================================

class MockPWItemController : public Lineside::Notifiable<bool> {
public:
  MockPWItemController(Lineside::ItemId id) :
    Notifiable<bool>(),
    expectedId(id),
    gotNotification(false) {}
  
  virtual void Notify(const unsigned int sourceId,
		      const bool notification) override {
    BOOST_CHECK_EQUAL( sourceId, expectedId.Get() );
    BOOST_CHECK_EQUAL( notification, true ); // Per WakeController()
    this->gotNotification = true;
  }

  Lineside::ItemId expectedId;
  bool gotNotification;
};

// ======================================

BOOST_FIXTURE_TEST_SUITE(TrackCircuitMonitor, MockManagerFixture)

BOOST_AUTO_TEST_CASE(Construct)
{
  const Lineside::ItemId id(10);
  const std::string controller = "BIP";
  const std::string controllerData = "07";

  Lineside::TrackCircuitMonitorData tcmd;
  tcmd.id = id;
  tcmd.inputPinRequest.controller = controller;
  tcmd.inputPinRequest.controllerData = controllerData;

  auto pwItem = tcmd.Construct(this->hwManager, this->swManager);
  BOOST_REQUIRE( pwItem );
  BOOST_CHECK_EQUAL( pwItem->getId(), id );
  auto tcm = std::dynamic_pointer_cast<Lineside::TrackCircuitMonitor>(pwItem);
  BOOST_REQUIRE( tcm );
  BOOST_REQUIRE_EQUAL( tcm.use_count(), 2 ); // pwItem and tcm itself

  BOOST_CHECK_EQUAL( this->hwManager->bipProvider->pins.size(), 1 );
  auto bip = this->hwManager->bipProvider->pins.at(controllerData);
  BOOST_REQUIRE(bip);
}

BOOST_AUTO_TEST_CASE(SetOccupiedUnOccupied)
{
  const Lineside::ItemId id(10);
  const std::string controller = "BIP";
  const std::string controllerData = "07";

  Lineside::TrackCircuitMonitorData tcmd;
  tcmd.id = id;
  tcmd.inputPinRequest.controller = controller;
  tcmd.inputPinRequest.controllerData = controllerData;

  auto pwItem = tcmd.Construct(this->hwManager, this->swManager);
  BOOST_REQUIRE( pwItem );
  BOOST_CHECK_EQUAL( pwItem->getId(), id );
  auto tcm = std::dynamic_pointer_cast<Lineside::TrackCircuitMonitor>(pwItem);
  BOOST_REQUIRE( tcm );

  auto mockPWItemController = std::make_shared<MockPWItemController>(id);
  tcm->RegisterController( tcm->getId().Get(), mockPWItemController );
  BOOST_CHECK_EQUAL( id, mockPWItemController->expectedId );
  
  auto mockBIP = this->hwManager->bipProvider->pins.at(controllerData);
  BOOST_REQUIRE( mockBIP );
  BOOST_CHECK_EQUAL( mockBIP->Get(), false );
  BOOST_CHECK_EQUAL( tcm->GetState(), false );

  mockPWItemController->gotNotification = false;
  mockBIP->Set(true);
  BOOST_CHECK_EQUAL( tcm->GetState(), true );
  BOOST_CHECK_EQUAL( mockPWItemController->gotNotification, true );

  mockPWItemController->gotNotification = false;
  mockBIP->Set(false);
  BOOST_CHECK_EQUAL( tcm->GetState(), false );
  BOOST_CHECK_EQUAL( mockPWItemController->gotNotification, true );
}

BOOST_AUTO_TEST_CASE(OnRunSendsToRTC)
{
  BOOST_FAIL("Unimplemented");
}


BOOST_AUTO_TEST_SUITE_END()
