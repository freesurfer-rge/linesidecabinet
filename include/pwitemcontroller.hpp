#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>

#include "notifiable.hpp"

#include "itemid.hpp"

namespace Lineside {
  class PWItemModel;

  //! Contoller for a Permanent Way Item
  class PWItemController : public Notifiable<bool> {
  public:
    virtual ~PWItemController();
    
    void Activate();
    
    void Deactivate();

    virtual void Notify(const unsigned int sourceId,
			const bool notification) override;

    static std::shared_ptr<PWItemController> Construct(std::shared_ptr<PWItemModel> pwim);
    
  private:
    enum class ControllerState { Constructed, Active, Inactive };
    const std::chrono::seconds MaximumWaitSeconds = std::chrono::seconds(5);
    
    std::shared_ptr<PWItemModel> model;
    ItemId id;
    ControllerState state;

    std::thread t;
    std::mutex mtx;
    std::condition_variable cv;
    
    PWItemController() :
      Notifiable<bool>(),
      model(),
      id(),
      state(ControllerState::Constructed),
      t(),
      mtx(),
      cv() {
      // Nothing to do
    }

    bool CheckWakeUp() const;

    void Run();
  };
}
