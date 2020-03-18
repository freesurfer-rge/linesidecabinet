#pragma once

#include <string>
#include <map>

#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOMElement.hpp>

namespace Lineside {
  namespace xml {
    class SettingsReader {
    public:
      std::map<std::string,std::string> Read( const xercesc::DOMElement *parent ) const;
    };
  }
}
