#pragma once

#include <memory>
#include <mutex>

#include "tendril/notifiable.hpp"
#include "tendril/notifier.hpp"

namespace Tendril {
  //! Class representing the concept of an input pin
  /*!
    Consuming libraries can interact with input pins in two ways.
    They can query the state of the pin directly, or they can register listeners, which
    are called whenever the state of the pin changes.
   */
  class BinaryInputPin {
  public:
    BinaryInputPin() :
      notifyMutex(),
      notifier() {}

    virtual ~BinaryInputPin() {}

    //! Retrieve the current state of the pin
    virtual bool Get() const = 0;

    //! Registers a listener
    /*!
      Listeners are objects which wish to be notified of changes in state.
      Multiple listeners can be registered for a single pin.

      @param listener Pointer to the object which wishes to receive notifications
     */
    void RegisterListener(std::weak_ptr<Notifiable<bool>> listener);

  protected:
    //! Mutex for everything to do with notifications
    std::mutex notifyMutex;

    //! Sends the notifications (uses mutex)
    /*!
      Implementations of this class should call this
      method when the pin changes state.

      @param latestValue The new state of the pin
     */
    void NotifyUpdate(const bool latestValue);

  private:
    Notifier<bool> notifier;
  };
}
