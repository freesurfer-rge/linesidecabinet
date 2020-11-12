#pragma once

#include "tendril/boparray.hpp"
#include "tendril/tendriltypes.hpp"

namespace Tendril::Mocks {
  class MockBOPArray : public BOPArray {
  public:
    MockBOPArray(const size_t nPins)
      : BOPArray(nPins),
	outputs(nPins),
	settings() {}

    virtual void Update() override;

    std::vector<bool> outputs;
    
    SettingsMap settings;
  };
}
