#pragma once

#include <xercesc/dom/DOMElement.hpp>

#include "tendril/devices/i2cdevicedata.hpp"

#include "lineside/xml/devicedatareader.hpp"

namespace Lineside::xml {
  //! Class to read in data about a straightforward I2C Device
  /*!
    This should be used for anything which uses a plain
    I2CDeviceData<DeviceType> data structure
  */
  template<typename DeviceType>
  class I2CDeviceDataReader : public DeviceDataReader {
  public:
    
  };
}
