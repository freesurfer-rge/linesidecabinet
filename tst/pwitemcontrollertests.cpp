#include <cmath>

#include <boost/test/unit_test.hpp>

#include "pwitemmodel.hpp"
#include "pwitemcontroller.hpp"

#include "exceptionmessagecheck.hpp"

// ===================================

class MockModel : public Lineside::PWItemModel {
public:
  MockModel(Lineside::ItemId id) :
    Lineside::PWItemModel(id),
    onActivateCalled(false),
    onDeactivateCalled(false),
    runThreadId(),
    onRunCallTimes(),
    onRunWait(100),
    stateChange(false) {}
  
  virtual void OnActivate() override {
    if(this->onActivateCalled) {
      throw std::logic_error("Double call OnActivate");
    }
    this->onActivateCalled = true;
    this->runThreadId = std::this_thread::get_id();
  }

  virtual void OnDeactivate() override {
    if(this->onDeactivateCalled) {
      throw std::logic_error("Double call OnDeactivate");
    }
    if( !this->onActivateCalled ) {
      throw std::logic_error("OnDeactivate called before OnActivate");
    }
    this->onDeactivateCalled = true;
  }

  virtual std::chrono::milliseconds OnRun() override {
    this->onRunCallTimes.push_back(std::chrono::high_resolution_clock::now());
    return this->onRunWait;
  }

  virtual bool HaveStateChange() override {
    bool result = this->stateChange;
    this->stateChange = false;
    return result;
  }

  bool onActivateCalled;
  bool onDeactivateCalled;
  std::thread::id runThreadId;
  std::vector<std::chrono::high_resolution_clock::time_point> onRunCallTimes;
  std::chrono::milliseconds onRunWait;
  bool stateChange;
};

// ===================================

const std::chrono::milliseconds timeFuzz(10);

void PauseForThread() {
  // We are managing a separate thread, but have no direct
  // visibility. Wait a short time to give it an opportunity
  // to run before performing checks
  // Of course, this is still not an absolute guarantee
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

// ===================================

BOOST_AUTO_TEST_SUITE(PWItemController)

BOOST_AUTO_TEST_CASE(BasicLifeCycle, *boost::unit_test::timeout(2))
{
  Lineside::ItemId id = Lineside::ItemId::Random();
  auto model = std::make_shared<MockModel>(id);

  auto controller = std::make_shared<Lineside::PWItemController>(model);
  BOOST_CHECK_EQUAL(controller.use_count(), 1);
  BOOST_CHECK(!model->onActivateCalled);
  BOOST_CHECK_EQUAL(model->onRunCallTimes.size(), 0);

  controller->Activate();
  BOOST_CHECK(model->onActivateCalled);
  BOOST_CHECK( std::this_thread::get_id() != model->runThreadId );

  // Following may fail if thread scheduling is particularly
  // weird
  BOOST_CHECK_EQUAL(model->onRunCallTimes.size(), 1);

  controller->Deactivate();
  PauseForThread();
  BOOST_CHECK( model->onDeactivateCalled );

  // Since we only had a short pause, should not have
  // had more OnRun() calls
  BOOST_CHECK_EQUAL(model->onRunCallTimes.size(), 1);
}

BOOST_AUTO_TEST_CASE(ShortDurationSleeps, *boost::unit_test::timeout(2))
{
  Lineside::ItemId id = Lineside::ItemId::Random();
  auto model = std::make_shared<MockModel>(id);
  auto controller = std::make_shared<Lineside::PWItemController>(model);
  BOOST_CHECK_EQUAL(model->onRunCallTimes.size(), 0);

  const int nSleepIntervals = 10;
  
  controller->Activate();
  // Let OnRun() be called a few times
  std::this_thread::sleep_for(model->onRunWait * nSleepIntervals);
  controller->Deactivate();

  // Check how many times OnRun() was called
  double countDeviation = model->onRunCallTimes.size() - nSleepIntervals;
  BOOST_CHECK( std::abs(countDeviation) <= 1 );

  // Check the call times
  for( size_t i=1; i<model->onRunCallTimes.size(); i++ ) {
    auto timediff = model->onRunCallTimes.at(i) - model->onRunCallTimes.at(i-1);

    // No abs() for duration objects....
    auto deviation = timediff - model->onRunWait;
    BOOST_CHECK( deviation < timeFuzz );
    BOOST_CHECK( -deviation < timeFuzz );
  }
}

BOOST_AUTO_TEST_CASE(LongSleepIgnored, *boost::unit_test::timeout(30))
{
  Lineside::ItemId id = Lineside::ItemId::Random();
  auto model = std::make_shared<MockModel>(id);
  auto controller = std::make_shared<Lineside::PWItemController>(model);
  BOOST_CHECK_EQUAL(model->onRunCallTimes.size(), 0);

  // Set too long sleep request
  model->onRunWait = std::chrono::seconds(20);

  controller->Activate();
  std::this_thread::sleep_for(std::chrono::seconds(25));

  // Should get at least four OnRun() calls due to MaximumWaitTime
  BOOST_CHECK_GE( model->onRunCallTimes.size(), 4 );
  
}

BOOST_AUTO_TEST_CASE(DestructorDeactivates, *boost::unit_test::timeout(2))
{
  Lineside::ItemId id = Lineside::ItemId::Random();
  auto model = std::make_shared<MockModel>(id);
  model->onRunWait = std::chrono::seconds(4);
  {
    auto controller = std::make_shared<Lineside::PWItemController>(model);
    controller->Activate();
  }
  BOOST_CHECK( model->onDeactivateCalled );
}

BOOST_AUTO_TEST_CASE(ModelCanNotify, *boost::unit_test::timeout(2))
{
  Lineside::ItemId id = Lineside::ItemId::Random();
  auto model = std::make_shared<MockModel>(id);
  auto controller = std::make_shared<Lineside::PWItemController>(model);
  BOOST_CHECK_EQUAL(model->onRunCallTimes.size(), 0);

  model->onRunWait = std::chrono::seconds(4);
  controller->Activate();

  auto notificationTime = std::chrono::high_resolution_clock::now();
  model->WakeController();
  PauseForThread();
  controller->Deactivate();

  auto lastOnRunTime = model->onRunCallTimes.back();
  auto timeDiff = lastOnRunTime - notificationTime;
  BOOST_CHECK( timeDiff < timeFuzz );
}

BOOST_AUTO_TEST_CASE(IncorrectActivate, *boost::unit_test::timeout(2))
{
  Lineside::ItemId id = Lineside::ItemId::Random();
  auto model = std::make_shared<MockModel>(id);
  auto controller = std::make_shared<Lineside::PWItemController>(model);

  controller->Activate();

  std::stringstream msg;
  msg << "Improper Activate() call on " << id;

  // Do a second activate
  BOOST_CHECK_EXCEPTION( controller->Activate(),
			 std::logic_error,
			 GetExceptionMessageChecker<std::logic_error>( msg.str() ) );
  
  // Also can't re-activate
  controller->Deactivate();
  BOOST_CHECK_EXCEPTION( controller->Activate(),
			 std::logic_error,
			 GetExceptionMessageChecker<std::logic_error>( msg.str() ) );
}

BOOST_AUTO_TEST_CASE(DeactivateWithoutActivate, *boost::unit_test::timeout(1))
{
  Lineside::ItemId id = Lineside::ItemId::Random();
  auto model = std::make_shared<MockModel>(id);
  auto controller = std::make_shared<Lineside::PWItemController>(model);

  BOOST_CHECK_NO_THROW( controller->Deactivate() );
}

BOOST_AUTO_TEST_SUITE_END()
