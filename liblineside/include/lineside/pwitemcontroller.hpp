#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>

#include "lineside/notifiable.hpp"

#include "lineside/itemid.hpp"

namespace Lineside {
  class PWItemModel;

  //! Controller for a Permanent Way Item
  /*!
    This class is responsible for the _managing_ thread associated with an item
    on the permanent way (such as a multiaspect signal head or a track circuit).
    The state of the item itself is the responsibility of the corresponding
    PWItemModel object.
   */
  class PWItemController : public Notifiable<bool> {
  public:
    //! Default value for the maximum interval between OnRun method calls
    static constexpr std::chrono::seconds DefaultMaximumWaitSeconds = std::chrono::seconds(120);
    
    virtual ~PWItemController();

    //! Start up the managing thread and use it to run the model
    void Activate();

    //! Shut down the managing thread
    void Deactivate();

    virtual void Notify(const unsigned int sourceId,
			const bool notification) override;

    //! Get the associated PWItemModel
    PWItemModel& GetModel() const;

    //! Create a PWItemController for the supplied model
    static std::shared_ptr<PWItemController> Construct(std::shared_ptr<PWItemModel> pwim);

    //! The maximum number of seconds before the OnRun method will be called again
    static std::chrono::seconds MaximumWaitSeconds;
  private:
    enum class ControllerState { Constructed, Active, Inactive };
    
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
