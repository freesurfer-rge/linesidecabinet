#pragma once

#include <xercesc/dom/DOMElement.hpp>

#include "hardwaremanagerdata.hpp"

namespace Lineside {
  namespace xml {
    //! Class to read in data to construct the HardwareManager
    class HardwareManagerDataReader {
    public:
      const std::string HardwareManagerElement = "HardwareManager";

      bool HasHardwareManager( const xercesc::DOMElement *parent ) const;

      xercesc::DOMElement* GetHardwareManagerElement( const xercesc::DOMElement *parent ) const;

      Lineside::HardwareManagerData Read( const xercesc::DOMElement *hardwaremanagerElement ) const;
    };
  }
}
