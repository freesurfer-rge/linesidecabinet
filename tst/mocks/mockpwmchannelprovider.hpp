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
  
  virtual std::weak_ptr<Lineside::PWMChannel> GetHardware(const std::string& hardwareId,
							  const std::map<std::string,std::string>& settings) override;

  std::map<std::string,std::shared_ptr<MockPWMChannel>> channels;
};
