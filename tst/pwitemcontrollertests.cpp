#include <boost/test/unit_test.hpp>

#include "pwitemmodel.hpp"
#include "pwitemcontroller.hpp"

// ===================================

class MockModel : public Lineside::PWItemModel {
public:
  MockModel(Lineside::ItemId id) : Lineside::PWItemModel(id) {}
  
  virtual void OnActivate() override {
    throw std::logic_error(__PRETTY_FUNCTION__);
  }

  virtual void OnDeactivate() override {
    throw std::logic_error(__PRETTY_FUNCTION__);
  }

  virtual std::chrono::milliseconds OnRun() override {
    throw std::logic_error(__PRETTY_FUNCTION__);
  }

  virtual bool HaveStateChange() override {
    throw std::logic_error(__PRETTY_FUNCTION__);
  }
};

// ===================================

BOOST_AUTO_TEST_SUITE(PWItemController)

BOOST_AUTO_TEST_CASE(BasicLifeCycle)
{
  Lineside::ItemId id = Lineside::ItemId::Random();
  auto model = std::make_shared<MockModel>(id);

  auto controller = std::make_shared<Lineside::PWItemController>(model);
  BOOST_CHECK_EQUAL(controller.use_count(), 1);
}

BOOST_AUTO_TEST_SUITE_END()
