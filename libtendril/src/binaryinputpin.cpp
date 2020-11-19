#include "tendril/binaryinputpin.hpp"

namespace Tendril {
  void
  BinaryInputPin::RegisterListener(std::weak_ptr<Notifiable<bool>> listener) {
    std::lock_guard<std::mutex> lock(this->notifyMutex);
    this->notifier.Register(listener);
  }

  void
  BinaryInputPin::NotifyUpdate() {
    std::lock_guard<std::mutex> lock(this->notifyMutex);
    this->notifier.Notify(this->Get());
  }
}
