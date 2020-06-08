#pragma once

#include "lineside/binaryoutputpin.hpp"

class MockBOP : public Lineside::BinaryOutputPin {
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
