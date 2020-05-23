#include <iostream>

#include "stubsoftwaremanager.hpp"

void StubRTCClient::SendTrackCircuitNotification(const Lineside::ItemId trackCircuitId,
						 const bool occupied ) {
  std::cout << __FUNCTION__ << ": "
	    << trackCircuitId << " "
	    << occupied << std::endl;
}

std::shared_ptr<Lineside::RTCClient> StubSoftwareManager::GetRTCClient() {
  auto result = std::make_shared<StubRTCClient>();

  this->rtcClientList.push_back(result);

  return result;
}
