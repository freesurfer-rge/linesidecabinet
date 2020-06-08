#pragma once

#include <chrono>

#include "notifier.hpp"

#include "itemid.hpp"

namespace Lineside {
  //! Base class for Permanent Way Items
  /*!
    These are the pieces of hardware monitored or controlled by this program.
    Some examples are track circuits and turnout motors. This class works
    together with the PWItemController, which is responsible for managing
    the thread which runs instances of this class.

    Code in this class is executed by either the _managing_ thread (owned by
    the associated PWItemController) or the _main_ thread (of the program).
   */
  class PWItemModel {
  public:
    PWItemModel(const ItemId itemId) :
      id(itemId),
      controllerNotifier() {}
    
    virtual ~PWItemModel() {}

    //! Returns the id of this permanent way item
    ItemId getId() const {
      return this->id;
    }

    //! Hook to perform any required setup tasks on the managing thread
    virtual void OnActivate() {}

    //! Hook to perform any required tasks prior to the termination of the managing thread
    virtual void OnDeactivate() {}

    //! Hook to interact with the hardware
    /*!
      The managing thread calls this repeatedly, enabling the subclasses to
      manipulate their associated hardware. The return value is a request for
      a sleep interval before this method is called again (if WakeController()
      is not called first).

      \b Note The PWItemController class caps the time which may elapse prior
      to the next call of this method. It is not possible to request to sleep
      until there is a state change. Subclasses should ensure that their
      implementations of this method are suitably idempotent.

      \retval Requested time before next call
     */
    virtual std::chrono::milliseconds OnRun() = 0;

    //! Indicate whether or not the state of the item needs to change
    /*!
      This method is used to guard against spurious wakeups of the
      managing thread. The OnRun() method will only be called if
      this method returns true (or the duration specified by the
      last OnRun() call has elapsed).
     */
    virtual bool HaveStateChange() = 0;

    //! Setup the communication link between this object and the corresponding PWItemController
    void RegisterController(const unsigned int reqSrcId,
			    std::weak_ptr<Notifiable<bool>> target);

    //! Sends a wake up notification to the managing thread
    void WakeController();
  private:
    ItemId id;
    Notifier<bool> controllerNotifier;
  };
}
