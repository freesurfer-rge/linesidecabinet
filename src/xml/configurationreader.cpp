#include "xml/configurationreader.hpp"

namespace Lineside {
  namespace xml {
    ConfigurationData ConfigurationReader::Read( const std::string filePath ) const {
      if( filePath.empty() ) {
	throw std::logic_error("Empty filePath");
      }
      
      ConfigurationData result;

      return result;
    }
  }
}
