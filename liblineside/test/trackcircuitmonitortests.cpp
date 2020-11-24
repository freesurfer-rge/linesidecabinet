#include <boost/test/unit_test.hpp>

#include "tendril/mocks/mockbip.hpp"
#include "tendril/mocks/mockhardwareprovider.hpp"
#include "tendril/mocks/utilities.hpp"

#include "lineside/trackcircuitmonitordata.hpp"
#include "lineside/trackcircuitmonitor.hpp"

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
  const std::string controller = Tendril::Mocks::BIPProviderId;
  const std::string controllerData = "07";

  Lineside::TrackCircuitMonitorData tcmd;
  tcmd.id = id;
  tcmd.sensor = Lineside::TrackCircuitSensor::OccupiedIsHigh;
  tcmd.inputPinRequest.controller = controller;
  tcmd.inputPinRequest.controllerData = controllerData;

  auto pwItem = tcmd.Construct(*(this->hwManager), *(this->swManager));
  BOOST_REQUIRE( pwItem );
  BOOST_CHECK_EQUAL( pwItem->getId(), id );
  auto tcm = std::dynamic_pointer_cast<Lineside::TrackCircuitMonitor>(pwItem);
  BOOST_REQUIRE( tcm );
  BOOST_REQUIRE_EQUAL( tcm.use_count(), 2 ); // pwItem and tcm itself

  auto mockProvider = this->hwManager->bipProviderRegistrar.Retrieve(controller);
  auto mockbipProvider = std::dynamic_pointer_cast<Tendril::Mocks::MockHardwareProvider<Tendril::BinaryInputPin, Tendril::Mocks::MockBIP>>(mockProvider);
  BOOST_REQUIRE(mockbipProvider);
  auto bip = mockbipProvider->hardware.at(controllerData);
  BOOST_REQUIRE(bip);
}

BOOST_AUTO_TEST_CASE(SetOccupiedUnOccupiedHigh)
{
  const Lineside::ItemId id(10);
  const std::string controller = Tendril::Mocks::BIPProviderId;
  const std::string controllerData = "07";

  Lineside::TrackCircuitMonitorData tcmd;
  tcmd.id = id;
  tcmd.sensor = Lineside::TrackCircuitSensor::OccupiedIsHigh; // Compare next test
  tcmd.inputPinRequest.controller = controller;
  tcmd.inputPinRequest.controllerData = controllerData;

  auto pwItem = tcmd.Construct(*(this->hwManager), *(this->swManager));
  BOOST_REQUIRE( pwItem );
  BOOST_CHECK_EQUAL( pwItem->getId(), id );
  auto tcm = std::dynamic_pointer_cast<Lineside::TrackCircuitMonitor>(pwItem);
  BOOST_REQUIRE( tcm );

  auto mockPWItemController = std::make_shared<MockPWItemController>(id);
  tcm->RegisterController( tcm->getId().Get(), mockPWItemController );
  BOOST_CHECK_EQUAL( id, mockPWItemController->expectedId );

  auto mockProvider = this->hwManager->bipProviderRegistrar.Retrieve(controller);
  auto mockbipProvider = std::dynamic_pointer_cast<Tendril::Mocks::MockHardwareProvider<Tendril::BinaryInputPin, Tendril::Mocks::MockBIP>>(mockProvider);
  BOOST_REQUIRE(mockbipProvider);
  auto bip = mockbipProvider->hardware.at(controllerData);
  BOOST_REQUIRE(bip);
  BOOST_CHECK_EQUAL( bip->Get(), false );
  BOOST_CHECK_EQUAL( tcm->GetState(), false );

  mockPWItemController->gotNotification = false;
  bip->state = true;
  bip->SendNotifications();
  BOOST_CHECK_EQUAL( tcm->GetState(), true );
  BOOST_CHECK_EQUAL( mockPWItemController->gotNotification, true );

  mockPWItemController->gotNotification = false;
  bip->state = false;
  bip->SendNotifications();
  BOOST_CHECK_EQUAL( tcm->GetState(), false );
  BOOST_CHECK_EQUAL( mockPWItemController->gotNotification, true );
}

BOOST_AUTO_TEST_CASE(SetOccupiedUnOccupiedLow)
{
  const Lineside::ItemId id(10);
  const std::string controller = Tendril::Mocks::BIPProviderId;
  const std::string controllerData = "07";

  Lineside::TrackCircuitMonitorData tcmd;
  tcmd.id = id;
  tcmd.sensor = Lineside::TrackCircuitSensor::OccupiedIsLow; // Compare previous test
  tcmd.inputPinRequest.controller = controller;
  tcmd.inputPinRequest.controllerData = controllerData;

  auto pwItem = tcmd.Construct(*(this->hwManager), *(this->swManager));
  BOOST_REQUIRE( pwItem );
  BOOST_CHECK_EQUAL( pwItem->getId(), id );
  auto tcm = std::dynamic_pointer_cast<Lineside::TrackCircuitMonitor>(pwItem);
  BOOST_REQUIRE( tcm );

  auto mockPWItemController = std::make_shared<MockPWItemController>(id);
  tcm->RegisterController( tcm->getId().Get(), mockPWItemController );
  BOOST_CHECK_EQUAL( id, mockPWItemController->expectedId );
  
  auto mockProvider = this->hwManager->bipProviderRegistrar.Retrieve(controller);
  auto mockbipProvider = std::dynamic_pointer_cast<Tendril::Mocks::MockHardwareProvider<Tendril::BinaryInputPin, Tendril::Mocks::MockBIP>>(mockProvider);
  BOOST_REQUIRE(mockbipProvider);
  auto bip = mockbipProvider->hardware.at(controllerData);
  BOOST_REQUIRE( bip );
  BOOST_CHECK_EQUAL( bip->Get(), false );
  BOOST_CHECK_EQUAL( tcm->GetState(), true );

  mockPWItemController->gotNotification = false;
  bip->state = true;
  bip->SendNotifications();
  BOOST_CHECK_EQUAL( tcm->GetState(), false );
  BOOST_CHECK_EQUAL( mockPWItemController->gotNotification, true );

  mockPWItemController->gotNotification = false;
  bip->state = false;
  bip->SendNotifications();
  BOOST_CHECK_EQUAL( tcm->GetState(), true );
  BOOST_CHECK_EQUAL( mockPWItemController->gotNotification, true );
}


BOOST_AUTO_TEST_CASE(OnRunSendsToRTC)
{
  const Lineside::ItemId id(10);
  const std::string controller = Tendril::Mocks::BIPProviderId;
  const std::string controllerData = "07";
  const std::chrono::seconds expectedSleepRequest = std::chrono::seconds(60);

  Lineside::TrackCircuitMonitorData tcmd;
  tcmd.id = id;
  tcmd.sensor = Lineside::TrackCircuitSensor::OccupiedIsHigh;
  tcmd.inputPinRequest.controller = controller;
  tcmd.inputPinRequest.controllerData = controllerData;

  auto pwItem = tcmd.Construct(*(this->hwManager), *(this->swManager));
  BOOST_REQUIRE( pwItem );
  BOOST_CHECK_EQUAL( pwItem->getId(), id );
  auto tcm = std::dynamic_pointer_cast<Lineside::TrackCircuitMonitor>(pwItem);
  BOOST_REQUIRE( tcm );

  auto mockPWItemController = std::make_shared<MockPWItemController>(id);
  tcm->RegisterController( tcm->getId().Get(), mockPWItemController );
  BOOST_CHECK_EQUAL( id, mockPWItemController->expectedId );
  
  auto mockProvider = this->hwManager->bipProviderRegistrar.Retrieve(controller);
  auto mockbipProvider = std::dynamic_pointer_cast<Tendril::Mocks::MockHardwareProvider<Tendril::BinaryInputPin, Tendril::Mocks::MockBIP>>(mockProvider);
  BOOST_REQUIRE(mockbipProvider);
  auto bip = mockbipProvider->hardware.at(controllerData);
  BOOST_REQUIRE( bip );
  BOOST_CHECK_EQUAL( bip->Get(), false );
  BOOST_CHECK_EQUAL( tcm->GetState(), false );

  BOOST_CHECK_EQUAL( this->swManager->rtcClientList.size(), 1 );
  auto mockRTC = this->swManager->rtcClientList.at(0);
  BOOST_CHECK_EQUAL( mockRTC->lastItemId.Get(), 0 );

  // Have TCM send unconditionally
  auto sleepTime = pwItem->OnRun();
  BOOST_CHECK( sleepTime == expectedSleepRequest );
  BOOST_CHECK_EQUAL( mockRTC->lastItemId, id );
  BOOST_CHECK_EQUAL( mockRTC->lastOccupied, false );
  mockRTC->lastItemId = Lineside::ItemId(0);

  // Check that there's no state change registering
  BOOST_CHECK_EQUAL( pwItem->HaveStateChange(), false );

  // Set the input to occupied
  bip->state = true;
  bip->SendNotifications();
  BOOST_CHECK_EQUAL( pwItem->HaveStateChange(), true );

  // Send again, will no longer have state change
  sleepTime = pwItem->OnRun();
  BOOST_CHECK( sleepTime == expectedSleepRequest );
  BOOST_CHECK_EQUAL( mockRTC->lastItemId, id );
  BOOST_CHECK_EQUAL( mockRTC->lastOccupied, true );
  BOOST_CHECK_EQUAL( pwItem->HaveStateChange(), false );
  mockRTC->lastItemId = Lineside::ItemId(0);

  // Set back to unoccupied
  bip->state = false;
  bip->SendNotifications();
  BOOST_CHECK_EQUAL( pwItem->HaveStateChange(), true );

  
  // Send again, will no longer have state change
  sleepTime = pwItem->OnRun();
  BOOST_CHECK( sleepTime == expectedSleepRequest );
  BOOST_CHECK_EQUAL( mockRTC->lastItemId, id );
  BOOST_CHECK_EQUAL( mockRTC->lastOccupied, false );
  BOOST_CHECK_EQUAL( pwItem->HaveStateChange(), false );
  mockRTC->lastItemId = Lineside::ItemId(0);
}

BOOST_AUTO_TEST_SUITE_END()
