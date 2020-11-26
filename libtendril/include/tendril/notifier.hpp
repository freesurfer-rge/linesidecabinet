#pragma once

#include <vector>
#include <memory>

#include "tendril/notifiable.hpp"

namespace Tendril {
  //! A class which can send notifications
  /*!
    Collaborates with the Notifiable class
    
    \tparam NotificationType The type of the messages passed as notifications
   */
  template<typename NotificationType>
  class Notifier {
  public:
    Notifier() :
      listeners() {}

    //! Add a notification target
    /*!
      A std::weak_ptr is stored, to help avoid reference counting disasters.

      @param target The object which wishes to receive notifications
     */
    void Register(std::weak_ptr<Notifiable<NotificationType>> target) {
      this->listeners.push_back(target);
    }

    //! Send notifications
    /*!
      If the std::weak_ptr to a particular target is no longer valid, it
      is silently skipped.

      @param notice The message to be passed to each target
    */
    void Notify(const NotificationType& notice) const {
      for( auto& it : this->listeners ) {
	// Get the shared_ptr
	auto listener = it.lock();

	if( listener ) {
	  listener->Notify(notice);
	}
      }
    }

  private:
    std::vector<std::weak_ptr<Notifiable<NotificationType>>> listeners;
  };
}
