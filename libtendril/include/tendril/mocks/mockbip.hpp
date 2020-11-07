#pragma once

#include "tendril/binaryinputpin.hpp"

namespace Tendril {
  namespace Mocks {
    class MockBIP : public BinaryInputPin {
    public:
      MockBIP()
	: BinaryInputPin(),
	  state(false) {}

      virtual bool Get() const override;

      void SendNotifications();
      
      bool state;
    };
  }
}
