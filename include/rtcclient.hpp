#pragma once

#include "itemid.hpp"

namespace Lineside {
  //! Abstraction for communication with rail traffic control
  class RTCClient {
  public:
    virtual ~RTCClient() {}

    virtual void SendTrackCircuitNotification( const ItemId trackCircuitId,
					       const bool occupied ) = 0;
  };
}
