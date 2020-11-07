#include "tendril/binaryinputpin.hpp"

namespace Tendril {
  void
  BinaryInputPin::RegisterListener(std::weak_ptr<Notifiable<bool>> listener) {
    this->notifier.Register(listener);
  }

  void
  BinaryInputPin::NotifyUpdate() {
    this->notifier.Notify(this->Get());
  }
}
