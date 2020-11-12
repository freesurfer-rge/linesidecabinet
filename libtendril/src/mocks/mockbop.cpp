#include "tendril/mocks/mockbop.hpp"

namespace Tendril {
  namespace Mocks {
    void MockBOP::Set(const bool level) {
      this->lastLevel = level;
    }
  }
}
