#pragma once

#include <memory>

#include "lineside/rtcclient.hpp"

namespace Lineside {
  //! Abstraction for access to software resources
  class SoftwareManager {
  public:
    virtual ~SoftwareManager() {}
    
    virtual std::shared_ptr<RTCClient> GetRTCClient() = 0;
  };
}
