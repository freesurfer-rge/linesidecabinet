#include "binaryinputpin.hpp"

namespace Lineside {
  void BinaryInputPin::RegisterListener(const int requestedSourceId,
					std::weak_ptr<Notifiable<bool>> listener) {
    throw std::logic_error(__FUNCTION__);
  }

  void BinaryInputPin::NotifyUpdate() {
    throw std::logic_error(__FUNCTION__);
  }
}
