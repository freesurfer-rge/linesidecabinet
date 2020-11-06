#pragma once

#include <vector>
#include <memory>

#include "tendril/notifiable.hpp"

namespace Tendril {
  template<typename NotificationType>
  class Notifier {
  public:
    Notifier() :
      listeners() {}

    void Register(std::weak_ptr<Notifiable<NotificationType>> target) {
      this->listeners.push_back(target);
    }

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
