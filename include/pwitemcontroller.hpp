#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>

#include "itemid.hpp"

namespace Lineside {
  class PWItemModel;
  
  //! Contoller for a Permanent Way Item
  class PWItemController {
  public:
    void Activate();

    void Run();
    
    void Deactivate();

    void NotifyUpdate();
  private:
    ItemId id;
    std::shared_ptr<PWItemModel> model;

    std::thread t;
    std::mutex mtx;
    std::condition_variable cv;
  };
}
