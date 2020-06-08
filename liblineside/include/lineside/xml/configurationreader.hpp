#pragma once

#include <string>

#include "lineside/configurationdata.hpp"

#include "lineside/xml/xercesguard.hpp"

namespace Lineside {
  namespace xml {
    //! Class to handle reading in the XML file
    class ConfigurationReader {
    public:
      const std::string LinesideCabinetElement = std::string("LinesideCabinet");
      
      ConfigurationReader() :
	libraryGuard() {}

      ConfigurationData Read( const std::string filePath ) const;
    private:
      XercesGuard libraryGuard;
    };
  }
}
