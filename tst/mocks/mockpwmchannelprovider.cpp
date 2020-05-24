#include <sstream>

#include "linesideexceptions.hpp"

#include "mockpwmchannelprovider.hpp"

std::unique_ptr<Lineside::PWMChannel>
MockPWMChannelProvider::GetHardware(const std::string& hardwareId,
				    const std::map<std::string,std::string>& settings) {
  if( settings.size() != 0 ) {
    std::stringstream msg;
    msg << "MockPWMChannel request for "
	<< hardwareId
	<< " did not have empty settings";
    throw std::logic_error(msg.str());
  }

  if( this->channels.count(hardwareId) != 0 ) {
    throw Lineside::DuplicateKeyException(hardwareId);
  }
  
  auto result = std::unique_ptr<MockPWMChannel>(new MockPWMChannel());
  this->channels[hardwareId] = result.get();
  return result;
}
