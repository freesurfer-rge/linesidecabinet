#include <stdexcept>
#include <boost/bimap.hpp>

#include "lineside/signalaspect.hpp"

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

  template<>
  SignalAspect Parse<SignalAspect>(const std::string& src) {
    if( convertor.empty() ) {
      initconvertor();
    }

    try {
      SignalAspect sa;
      sa = convertor.right.at(src);
      return sa;
    }
    catch( std::out_of_range& e ) {
      std::stringstream msg;
      msg << "Could not parse '";
      msg << src;
      msg << "' to SignalAspect";
      throw std::invalid_argument(msg.str());
    }
  }

  bool TryParse(const std::string& src, SignalAspect& dest) {
    if( convertor.empty() ) {
      initconvertor();
    }

    bool result = false;

    if( convertor.right.count(src) == 1 ) {
      result = true;
      dest = convertor.right.at(src);
    }

    return result;
  }
}
