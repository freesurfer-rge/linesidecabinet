#pragma once

#include <map>

#include "hardwareprovider.hpp"
#include "binaryinputpin.hpp"
#include "mockbip.hpp"

class MockBIPProvider : public Lineside::HardwareProvider<Lineside::BinaryInputPin> {
public:
  MockBIPProvider() :
    HardwareProvider(),
    pins() {}

  virtual std::unique_ptr<Lineside::BinaryInputPin> GetHardware(const std::string& hardwareId,
								const std::map<std::string,std::string>& settings) override;

  // Allow access to the created pins (dangerously)
  std::map<std::string,MockBIP*> pins;
};
