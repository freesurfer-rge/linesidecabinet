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
  class PWItemController : public Notifiable<bool>,
			   public std::enable_shared_from_this<PWItemController> {
  public:
    PWItemController(std::shared_ptr<PWItemModel> pwim) :
      model(pwim),
      id(pwim->getId()),
      state(ControllerState::Constructed),
      t(),
      mtx(),
      cv() {
      // Nothing to do
    }

    ~PWItemController();
    
    void Activate();

    void Run();
    
    void Deactivate();

    virtual void Notify(const unsigned int sourceId,
			const bool notification) override;
  private:
    enum class ControllerState { Constructed, Active, Inactive };
    const std::chrono::seconds MaximumWaitSeconds = std::chrono::seconds(5);
    
    std::shared_ptr<PWItemModel> model;
    ItemId id;
    ControllerState state;

    std::thread t;
    std::mutex mtx;
    std::condition_variable cv;

    bool CheckWakeUp() const;
  };
}
