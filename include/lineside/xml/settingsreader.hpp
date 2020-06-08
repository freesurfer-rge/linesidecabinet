#pragma once

#include <string>
#include <map>

#include <xercesc/dom/DOMElement.hpp>

namespace Lineside {
  namespace xml {
    class SettingsReader {
    public:
      bool HasSettings( const xercesc::DOMElement *parent ) const;
      
      xercesc::DOMElement* GetSettingsElement( const xercesc::DOMElement *parent ) const;
      
      std::map<std::string,std::string> Read( const xercesc::DOMElement *settingsElement ) const;
    };
  }
}
