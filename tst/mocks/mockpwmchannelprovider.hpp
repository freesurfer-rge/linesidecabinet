#pragma once

#include <map>

#include "hardwareprovider.hpp"
#include "pwmchannel.hpp"
#include "mockpwmchannel.hpp"

class MockPWMChannelProvider : public Lineside::HardwareProvider<Lineside::PWMChannel> {
public:
  MockPWMChannelProvider() :
    HardwareProvider(),
    channels() {}
  
  virtual std::unique_ptr<Lineside::PWMChannel> GetHardware(const std::string& hardwareId,
							    const std::map<std::string,std::string>& settings) override;

  // Allow dangerous access to the allocated channels
  std::map<std::string,MockPWMChannel*> channels;
};
