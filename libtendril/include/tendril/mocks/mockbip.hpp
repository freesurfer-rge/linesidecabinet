#pragma once

#include "tendril/binaryinputpin.hpp"
#include "tendril/tendriltypes.hpp"

namespace Tendril {
  namespace Mocks {
    class MockBIP : public BinaryInputPin {
    public:
      MockBIP()
	: BinaryInputPin(),
	  state(false),
	  settings() {}

      virtual bool Get() const override;

      void SendNotifications();
      
      bool state;
      
      SettingsMap settings;
    };
  }
}
