#include "tendril/mocks/mockpwmchannel.hpp"

namespace Tendril::Mocks {
  void MockPWMChannel::Set(const unsigned int start,
			   const unsigned int stop) {
    this->lastStart = start;
    this->lastStop = stop;
  }
}
