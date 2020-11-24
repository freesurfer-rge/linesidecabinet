#include "tendril/mocks/mockpwmchannel.hpp"

namespace Tendril::Mocks {
  void MockPWMChannel::Set(const unsigned int start,
			   const unsigned int stop) {
    auto next_update = std::make_pair(start, stop);
    this->updates.push_back(next_update);
  }
}
