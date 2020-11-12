#pragma once

#include <memory>

#include "tendril/notifiable.hpp"
#include "tendril/notifier.hpp"

namespace Tendril {
  class BinaryInputPin {
  public:
    BinaryInputPin() :
      notifier() {}

    virtual ~BinaryInputPin() {}

    virtual bool Get() const = 0;

    void RegisterListener(std::weak_ptr<Notifiable<bool>> listener);

  protected:
    void NotifyUpdate();

  private:
    Notifier<bool> notifier;
  };
}
