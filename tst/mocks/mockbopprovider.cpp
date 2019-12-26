#include "linesideexceptions.hpp"

#include "mockbopprovider.hpp"

std::weak_ptr<Lineside::BinaryOutputPin> MockBOPProvider::GetHardware(const std::string& hardwareId,
								      const std::map<std::string,std::string>& settings) {
  if( settings.size() != 0 ) {
    std::stringstream msg;
    msg << "MockBOP request for "
	<< hardwareId
	<< " did not have empty settings";
    throw std::logic_error(msg.str());
  }

  if( this->pins.count(hardwareId) != 0 ) {
    throw Lineside::DuplicateKeyException(hardwareId);
  }

  auto result = std::make_shared<MockBOP>();
  this->pins[hardwareId] = result;
  return result;
}
