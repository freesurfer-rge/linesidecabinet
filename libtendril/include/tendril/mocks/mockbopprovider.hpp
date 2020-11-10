#pragma once

#include <map>

#include "tendril/hardwareprovider.hpp"
#include "tendril/binaryoutputpin.hpp"

#include "tendril/mocks/mockbop.hpp"

namespace Tendril::Mocks {
  class MockBOPProvider : public HardwareProvider<BinaryOutputPin> {
  public:
    MockBOPProvider() :
      HardwareProvider(),
      pins() {}

    virtual std::unique_ptr<BinaryOutputPin>
    GetHardware(const std::string& hardwareId,
		const SettingsMap& settings) override;

    //! Allows (dangerous) access to returned resources
    std::map<std::string,MockBOP*> pins;
  };
}
