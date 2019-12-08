#include "binaryinputpin.hpp"

namespace Lineside {
  void BinaryInputPin::RegisterListener(const int requestedSourceId,
					std::weak_ptr<Notifiable<bool>> listener) {
    this->notifier.Register(requestedSourceId, listener);
  }

  void BinaryInputPin::NotifyUpdate() {
    this->notifier.Notify(this->Get());
  }
}
