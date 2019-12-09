#pragma once

#include <chrono>

#include "itemid.hpp"

namespace Lineside {
  class PWItemController;

  class PWItemModel {
  public:
    virtual void OnActivate() = 0;

    virtual void OnDeactivate() = 0;
    
    virtual std::chrono::milliseconds OnRun() = 0;

    virtual bool HaveStateChange() = 0;
  private:
    ItemId id;
    std::weak_ptr<PWItemController> controller;
  };
}
