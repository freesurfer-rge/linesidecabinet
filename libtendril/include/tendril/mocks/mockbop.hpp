#pragma once

#include "tendril/binaryoutputpin.hpp"

namespace Tendril {
  namespace Mocks {
    class MockBOP : public BinaryOutputPin {
    public:
      MockBOP() :
	BinaryOutputPin(),
	lastLevel(false) {};
      
      virtual void Set(const bool level) override;
      
      bool lastLevel;
    };
  }
}
