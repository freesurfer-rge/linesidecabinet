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
    PWItemController(std::shared_ptr<PWItemModel> pwim);

    ~PWItemController();
    
    void Activate();

    void Run();
    
    void Deactivate();
  private:
    enum class ControllerState { Constructed, Active, Inactive };
    
    ItemId id;
    std::shared_ptr<PWItemModel> model;
    ControllerState state;

    std::thread t;
    std::mutex mtx;
    std::condition_variable cv;
  };
}
