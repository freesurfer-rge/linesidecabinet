#pragma once

#include <chrono>

#include "notifier.hpp"

#include "itemid.hpp"

namespace Lineside {
  class PWItemModel {
  public:
    PWItemModel(const ItemId itemId) :
      id(itemId) {}
    
    virtual ~PWItemModel() {}

    ItemId getId() const {
      return this->id;
    }
    
    virtual void OnActivate() = 0;

    virtual void OnDeactivate() = 0;
    
    virtual std::chrono::milliseconds OnRun() = 0;

    virtual bool HaveStateChange() = 0;

    void RegisterController(const unsigned int reqSrcId,
			    std::weak_ptr<Notifiable<bool>> target);

    void WakeController();
  private:
    ItemId id;
    Notifier<bool> controllerNotifier;
  };
}
