#include "binaryinputpin.hpp"

namespace Lineside {
  void BinaryInputPin::RegisterListener(const int requestedSourceId,
					std::weak_ptr<Notifiable<bool>> listener) {
    this->listeners.push_back(Listener(requestedSourceId, listener));
  }

  void BinaryInputPin::NotifyUpdate() {
    for( auto it=this->listeners.begin(); it!=this->listeners.end(); ++it) {
      // Get a shared_ptr to the listener
      auto l = it->listener.lock();

      // Guard against expired pointers
      if( l.use_count() > 0 ) {
	l->Notify(it->requestedSourceId, this->Get());
      }
    }
  }
}
