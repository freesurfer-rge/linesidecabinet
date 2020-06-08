#pragma once

#include <xercesc/dom/DOMElement.hpp>

#include "lineside/softwaremanagerdata.hpp"

namespace Lineside {
  namespace xml {
    //! Class to read in data to construct the SoftwareManager
    class SoftwareManagerDataReader {
    public:
      const std::string SoftwareManagerElement = "SoftwareManager";
      const std::string RTCElement = "RTC";
      
      bool HasSoftwareManager( const xercesc::DOMElement *parent ) const;

      xercesc::DOMElement* GetSoftwareManagerElement( const xercesc::DOMElement *parent ) const;

      Lineside::SoftwareManagerData Read( const xercesc::DOMElement *softwaremanagerElement ) const;
    };
  }
}
