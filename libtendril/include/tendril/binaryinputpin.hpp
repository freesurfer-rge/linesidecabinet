#pragma once

#include <memory>
#include <mutex>

#include "tendril/notifiable.hpp"
#include "tendril/notifier.hpp"

namespace Tendril {
  class BinaryInputPin {
  public:
    BinaryInputPin() :
      notifyMutex(),
      notifier() {}

    virtual ~BinaryInputPin() {}

    virtual bool Get() const = 0;

    //! Registers a listener (using mutex)
    void RegisterListener(std::weak_ptr<Notifiable<bool>> listener);

  protected:
    //! Mutex for everything to do with notifications
    std::mutex notifyMutex;

    //! Sends the notifications (uses mutex)
    void NotifyUpdate();

  private:
    Notifier<bool> notifier;
  };
}
