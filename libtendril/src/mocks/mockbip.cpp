#include "tendril/mocks/mockbip.hpp"

namespace Tendril {
  namespace Mocks {
    bool MockBIP::Get() const {
      return this->state;
    }

    void MockBIP::SendNotifications() {
      this->NotifyUpdate(this->Get());
    }
  }
}
