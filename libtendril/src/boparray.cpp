#include "tendril/boparray.hpp"

namespace Tendril {
  void BOPArray::Set(const size_t i, const bool level) {
    this->pinState.at(i) = level;
  }
}
