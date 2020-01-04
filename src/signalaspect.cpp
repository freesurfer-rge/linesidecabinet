#include <stdexcept>
#include <boost/bimap.hpp>

#include "signalaspect.hpp"

namespace Lineside {
  std::ostream& operator<<( std::ostream& os, const SignalAspect s ) {
    os << ToString( s );
    
    return os;
  }

  std::string ToString( const SignalAspect s ) {
    if( s != SignalAspect::Red ) {
      throw std::logic_error(__PRETTY_FUNCTION__);
    }
    return std::string();
  }
}
