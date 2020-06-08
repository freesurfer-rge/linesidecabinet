#include "mocksoftwaremanager.hpp"

std::shared_ptr<Lineside::RTCClient> MockSoftwareManager::GetRTCClient() {
  auto nxt = std::make_shared<MockRTCClient>();

  this->rtcClientList.push_back(nxt);

  return nxt;
}
