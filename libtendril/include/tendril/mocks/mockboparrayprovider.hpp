#pragma once

#include "tendril/hardwareprovider.hpp"
#include "tendril/boparray.hpp"

#include "tendril/mocks/mockboparray.hpp"

namespace Tendril::Mocks {
  class MockBOPArrayProvider : public HardwareProvider<BOPArray> {
  public:
    MockBOPArrayProvider()
      : HardwareProvider(),
	hardware() {}

    virtual std::unique_ptr<BOPArray>
    GetHardware(const std::string& hardwareId,
		const SettingsMap& settings) override;

    std::map<std::string,MockBOPArray*> hardware;
  };
}
