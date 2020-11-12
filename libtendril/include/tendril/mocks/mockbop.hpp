#pragma once

#include "tendril/binaryoutputpin.hpp"
#include "tendril/tendriltypes.hpp"

namespace Tendril {
  namespace Mocks {
    class MockBOP : public BinaryOutputPin {
    public:
      MockBOP() :
	BinaryOutputPin(),
	lastLevel(false),
	settings() {};
      
      virtual void Set(const bool level) override;
      
      bool lastLevel;

      SettingsMap settings;
    };
  }
}
