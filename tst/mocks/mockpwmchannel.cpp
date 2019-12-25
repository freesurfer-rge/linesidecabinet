#include <iostream>

#include "mockpwmchannel.hpp"

void MockPWMChannel::Set(const unsigned int value) {
  this->state = value;
  auto update = std::make_pair( std::chrono::high_resolution_clock::now(), value );
  this->updates.push_back(update);
}

unsigned int MockPWMChannel::Get() const {
  return this->state;
}
