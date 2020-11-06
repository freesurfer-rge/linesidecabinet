#pragma once

#include <vector>
#include <memory>

#include "tentril/notifiable.hpp"

namespace Tentril {
  template<typename NotificationType>
  class Notifier {
  public:
    Notifier() :
      listeners() {}

    void Register(std::weak_ptr<Notifiable<NotificationType>> target) {
      this->listeners.push_back(target);
    }

    void Notify(const NotificationType& notice) const {
      for( auto it : this->listeners ) {
	// Get the shared_ptr
	auto listener = it->listener.lock();

	if( listener ) {
	  listener.notify(notice);
	}
      }
    }

  private:
    std::vector<std::weak_ptr<Notifiable<NotificationType>> listeners;
  };
}
