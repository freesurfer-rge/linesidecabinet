#pragma once

#include <map>

#include "hardwareprovider.hpp"
#include "binaryoutputpin.hpp"
#include "mockbop.hpp"

class MockBOPProvider : public Lineside::HardwareProvider<Lineside::BinaryOutputPin> {
public:
  MockBOPProvider() :
    HardwareProvider(),
    pins() {}

  virtual std::unique_ptr<Lineside::BinaryOutputPin> GetHardware(const std::string& hardwareId,
								 const std::map<std::string,std::string>& settings) override;

  // Allow dangerous access to the returned resources
  std::map<std::string,MockBOP*> pins;
};
