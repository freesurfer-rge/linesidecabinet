#include "tendril/mocks/mockboparray.hpp"

namespace Tendril::Mocks {
  void MockBOPArray::Update() {
    this->outputs = this->pinState;
  }
}
