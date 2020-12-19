#pragma once

#include <xercesc/dom/DOMElement.hpp>
#include "tendril/hardwarerequestdata.hpp"

namespace Lineside {
  namespace xml {
    //! Class for reading in a device request
    /*!
      The devices are things such as BinaryInputs, BinaryOutputs and PWMChannels
     */
    class HardwareRequestDataReader {
    public:
      //! Read in the data for a hardware request
      /*!
	The actual element type of the hardwareRequestElement will be
	BinaryInput, BinaryOutput, BOPArray or PWMChannel.
      */
      Tendril::HardwareRequestData Read( const xercesc::DOMElement *hardwareRequestElement ) const;
    };
  }
}
