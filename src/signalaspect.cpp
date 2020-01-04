#include <stdexcept>
#include <boost/bimap.hpp>

#include "signalaspect.hpp"

namespace Lineside {
  static boost::bimap<SignalAspect,std::string> convertor;

  static void initconvertor() {
    typedef decltype(convertor)::value_type pos;
    convertor.insert( pos(SignalAspect::Red, "Red") );
    convertor.insert( pos(SignalAspect::Yellow1, "Yellow1") );
    convertor.insert( pos(SignalAspect::Yellow2, "Yellow2") );
    convertor.insert( pos(SignalAspect::Green, "Green") );
  }
  
  std::ostream& operator<<( std::ostream& os, const SignalAspect s ) {
    os << ToString( s );
    
    return os;
  }

  std::string ToString( const SignalAspect s ) {
    if( convertor.empty() ) {
      initconvertor();
    }

    std::string res;
    try {
      res = convertor.left.at(s);
    }
    catch( std::out_of_range& e ) {
      std::stringstream msg;
      msg << "Unrecognised SignalAspect: ";
      msg << static_cast<int>(s);
      throw std::runtime_error(msg.str());
    }

    return res;
  }
}
