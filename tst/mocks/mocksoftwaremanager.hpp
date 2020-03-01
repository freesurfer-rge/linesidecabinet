#pragma once

#include "softwaremanager.hpp"

#include "mockrtcclient.hpp"

class MockSoftwareManager : public Lineside::SoftwareManager {
public:
  MockSoftwareManager() :
    SoftwareManager(),
    rtcClientList() {}

  virtual std::weak_ptr<Lineside::RTCClient> GetRTCClient() override;
  
  std::vector<std::shared_ptr<MockRTCClient>> rtcClientList;
};
