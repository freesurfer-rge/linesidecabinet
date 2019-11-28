#pragma once

#include "binaryinputpin.hpp"

class MockBIP : public Lineside::BinaryInputPin {
public:
  MockBIP() :
    BinaryInputPin(),
    state(false) {}
  
  virtual bool Get() const override;

  void Set(const bool level);
private:
  bool state;
};
