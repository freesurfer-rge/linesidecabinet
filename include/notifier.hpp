#pragma once

#include <memory>

#include "notifiable.hpp"

namespace Lineside {
  //! A template class for sending notifications
  template<typename NotificationType>
  class Notifier {
  public:
    Notifier() :
      listeners() {}
    
    void Register(const unsigned int requestedSourceId,
		  std::weak_ptr<Notifiable<NotificationType>> target) {
      this->listeners.push_back(Listener(requestedSourceId, target));
    }

    void Notify(const NotificationType& notice) const {
      for( auto it=this->listeners.begin(); it!=this->listeners.end(); ++it) {
	// Get a shared_ptr to the listener
	auto l = it->listener.lock();
	
	// Guard against expired pointers
	if( l.use_count() > 0 ) {
	  // Send the notifications
	  l->Notify(it->requestedSourceId, notice);
	}
      }
    }
    
  private:
    struct Listener {
      Listener(unsigned int reqSrcId, std::weak_ptr<Notifiable<NotificationType>> l) :
	requestedSourceId(reqSrcId),
	listener(l) {}
      
      const unsigned int requestedSourceId;
      std::weak_ptr<Notifiable<NotificationType>> listener;
    };
    
    std::vector<Listener> listeners;
  };
}
