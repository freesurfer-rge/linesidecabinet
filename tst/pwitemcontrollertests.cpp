#include <boost/test/unit_test.hpp>

#include "pwitemmodel.hpp"
#include "pwitemcontroller.hpp"

// ===================================

class MockModel : public Lineside::PWItemModel {
public:
  MockModel(Lineside::ItemId id) :
    Lineside::PWItemModel(id),
    onActivateCalled(false),
    onDeactivateCalled(false),
    runThreadId(),
    onRunCallTimes() {}
  
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
    throw std::logic_error(__PRETTY_FUNCTION__);
  }

  virtual bool HaveStateChange() override {
    throw std::logic_error(__PRETTY_FUNCTION__);
  }

  bool onActivateCalled;
  bool onDeactivateCalled;
  std::thread::id runThreadId;
  std::vector<std::chrono::high_resolution_clock::time_point> onRunCallTimes;
};

// ===================================

BOOST_AUTO_TEST_SUITE(PWItemController)

BOOST_AUTO_TEST_CASE(BasicLifeCycle)
{
  Lineside::ItemId id = Lineside::ItemId::Random();
  auto model = std::make_shared<MockModel>(id);

  auto controller = std::make_shared<Lineside::PWItemController>(model);
  BOOST_CHECK_EQUAL(controller.use_count(), 1);
  BOOST_CHECK(!model->onActivateCalled);
  BOOST_CHECK_EQUAL(model->onRunCallTimes.size(), 0);

  controller->Activate();
  BOOST_CHECK(model->onActivateCalled);
  BOOST_CHECK_EQUAL(model->onRunCallTimes.size(), 1);
  BOOST_CHECK( std::this_thread::get_id() != model->runThreadId );
}

BOOST_AUTO_TEST_SUITE_END()
