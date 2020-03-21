#pragma once

#include <xercesc/dom/DOMElement.hpp>
#include "devicerequestdata.hpp"

namespace Lineside {
  namespace xml {
    //! Class for reading in a device request
    /*!
      The devices are things such as BinaryInputs, BinaryOutputs and PWMChannels
     */
    class DeviceRequestDataReader {
    public:
      //! Read in the data for a device request
      /*!
	The actual element type of the deviceRequestElement will be
	BinaryInput, BinaryOutput or PWMChannel.
      */
      Lineside::DeviceRequestData Read( const xercesc::DOMElement *deviceRequestElement ) const;
    };
  }
}
