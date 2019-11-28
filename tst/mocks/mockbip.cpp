#include "mockbip.hpp"

bool MockBIP::Get() const {
  return this->state;
}

void MockBIP::Set(const bool level) {
  this->state = level;
  this->NotifyOneUpdate();
}
