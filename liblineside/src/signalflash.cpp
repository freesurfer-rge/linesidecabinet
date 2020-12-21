#include <stdexcept>
#include <boost/bimap.hpp>

#include "lineside/signalflash.hpp"

namespace Lineside {
  static boost::bimap<SignalFlash,std::string> convertor;

  static void initconvertor() {
    typedef decltype(convertor)::value_type pos;
    convertor.insert( pos(SignalFlash::Steady, "Steady") );
    convertor.insert( pos(SignalFlash::Flashing, "Flashing") );
  }
  
  std::ostream& operator<<( std::ostream& os, const SignalFlash s ) {
    os << ToString( s );
    
    return os;
  }

  std::string ToString( const SignalFlash s ) {
    if( convertor.empty() ) {
      initconvertor();
    }

    std::string res;
    try {
      res = convertor.left.at(s);
    }
    catch( std::out_of_range& e ) {
      std::stringstream msg;
      msg << "Unrecognised SignalFlash: ";
      msg << static_cast<int>(s);
      throw std::runtime_error(msg.str());
    }

    return res;
  }
  
  template<>
  SignalFlash Parse<SignalFlash>(const std::string& src) {
    if( convertor.empty() ) {
      initconvertor();
    }

    try {
      SignalFlash sf;
      sf = convertor.right.at(src);
      return sf;
    }
    catch( std::out_of_range& e ) {
      std::stringstream msg;
      msg << "Could not parse '";
      msg << src;
      msg << "' to SignalFlash";
      throw std::invalid_argument(msg.str());
    }
  }
}
