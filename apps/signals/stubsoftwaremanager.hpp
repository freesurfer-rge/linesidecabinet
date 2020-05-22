#pragma once

#include "rtcclient.hpp"
#include "softwaremanager.hpp"

class StubRTCClient : public Lineside::RTCClient {
public:
  StubRTCClient() : RTCClient() {}
  
  virtual void SendTrackCircuitNotification(const Lineside::ItemId trackCircuitId,
					    const bool occupied ) override;
};

class StubSoftwareManager : public Lineside::SoftwareManager {
public:
  StubSoftwareManager() :
    SoftwareManager(),
    rtcClientList() {}
  
  virtual std::weak_ptr<Lineside::RTCClient> GetRTCClient() override;
  
  std::vector<std::shared_ptr<StubRTCClient>> rtcClientList;
};
