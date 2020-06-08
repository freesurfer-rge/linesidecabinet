#pragma once

#include <vector>
#include <chrono>

#include "lineside/pwmchannel.hpp"

class MockPWMChannel : public Lineside::PWMChannel {
public:
  MockPWMChannel():
    PWMChannel(),
    updates(),
    state(0) {}

  virtual void Set(const unsigned int value) override;

  virtual unsigned int Get() const override;

  std::vector<std::pair<std::chrono::high_resolution_clock::time_point,unsigned int>> updates;
private:
  unsigned int state;
};
