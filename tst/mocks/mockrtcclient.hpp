#pragma once

#include "rtcclient.hpp"

class MockRTCClient : public Lineside::RTCClient {
public:
  MockRTCClient() :
    RTCClient(),
    lastItemId(),
    lastOccupied(false) {}

  virtual void SendTrackCircuitNotification( const Lineside::ItemId trackCircuitId,
					     const bool occupied ) override;

  Lineside::ItemId lastItemId;
  bool lastOccupied;
};
