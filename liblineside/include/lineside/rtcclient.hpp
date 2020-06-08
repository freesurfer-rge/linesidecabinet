#pragma once

#include "lineside/itemid.hpp"

namespace Lineside {
  //! Abstraction for communication with rail traffic control
  class RTCClient {
  public:
    virtual ~RTCClient() {}

    //! Send a message to rail traffic control from a TrackCircuit
    virtual void SendTrackCircuitNotification( const ItemId trackCircuitId,
					       const bool occupied ) = 0;
  };
}
