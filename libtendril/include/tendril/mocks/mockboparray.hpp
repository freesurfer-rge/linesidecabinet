#pragma once

#include "tendril/boparray.hpp"

namespace Tendril::Mocks {
  class MockBOPArray : public BOPArray {
  public:
    MockBOPArray(const size_t nPins)
      : BOPArray(nPins),
	outputs(nPins) {}

    virtual void Update() override;

    std::vector<bool> outputs;
  };
}
