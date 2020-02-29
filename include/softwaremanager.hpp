#pragma once

#include <memory>

#include "rtcclient.hpp"

namespace Lineside {
  //! Abstraction for access to software resources
  class SoftwareManager {
  public:
    virtual std::weak_ptr<RTCClient> GetRTCClient() = 0;
  };
}
