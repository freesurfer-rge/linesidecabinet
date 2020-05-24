#include "linesideexceptions.hpp"

#include "mockbipprovider.hpp"

std::unique_ptr<Lineside::BinaryInputPin>
MockBIPProvider::GetHardware(const std::string& hardwareId,
			     const std::map<std::string,std::string>& settings) {
  if( settings.size() != 0 ) {
    std::stringstream msg;
    msg << "MockBIP request for "
	<< hardwareId
	<< " did not have empty settings";
    throw std::logic_error(msg.str());
  }

  if( this->pins.count(hardwareId) != 0 ) {
    throw Lineside::DuplicateKeyException(hardwareId);
  }

  auto result = std::unique_ptr<MockBIP>(new MockBIP());
  this->pins[hardwareId] = result.get();
  return result;
}
