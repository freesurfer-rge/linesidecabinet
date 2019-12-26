#pragma once

#include "binaryoutputpin.hpp"

class MockBOP : public Lineside::BinaryInputPin {
public:
  MockBOP() :
    BinaryOutputPin(),
    state(false) {}
  
  virtual void Set(const bool level) override {
    this->state = level;
  }

  virtual bool Get() const override {
    return this->state;
  }
  
  bool state;
};
