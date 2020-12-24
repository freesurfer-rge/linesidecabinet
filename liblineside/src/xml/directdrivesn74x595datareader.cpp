#include "tendril/devices/directdrivesn74x595data.hpp"

#include "lineside/xml/directdrivesn74x595datareader.hpp"

namespace Lineside::xml {
  const std::string DirectDriveSN74x595DataReader::TagName = "DirectDriveSN74x595";

  std::shared_ptr<Tendril::Devices::DeviceData>
  DirectDriveSN74x595DataReader::Read(const xercesc::DOMElement *deviceDataElement) const {
    if( !deviceDataElement ) {
      throw std::logic_error("Bad deviceDataElement");
    }

    auto result = std::make_shared<Tendril::Devices::DirectDriveSN74x595Data>();

    return result;
  }
}
