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

  virtual std::shared_ptr<Lineside::BinaryOutputPin> GetHardware(const std::string& hardwareId,
								 const std::map<std::string,std::string>& settings) override;

  std::map<std::string,std::shared_ptr<MockBOP>> pins;
};
