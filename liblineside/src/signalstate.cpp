#include <stdexcept>
#include <boost/bimap.hpp>

#include "lineside/signalstate.hpp"

namespace Lineside {
  static boost::bimap<SignalState,std::string> convertor;

  static void initconvertor() {
    typedef decltype(convertor)::value_type pos;
    convertor.insert( pos(SignalState::Red, "Red") );
    convertor.insert( pos(SignalState::DoubleYellow, "DoubleYellow") );
    convertor.insert( pos(SignalState::Yellow, "Yellow") );
    convertor.insert( pos(SignalState::Green, "Green") );
  }
  
  std::ostream& operator<<( std::ostream& os, const SignalState s ) {
    os << ToString( s );
    
    return os;
  }

  std::string ToString( const SignalState s ) {
    if( convertor.empty() ) {
      initconvertor();
    }

    std::string res;
    try {
      res = convertor.left.at(s);
    }
    catch( std::out_of_range& e ) {
      std::stringstream msg;
      msg << "Unrecognised SignalState: ";
      msg << static_cast<int>(s);
      throw std::runtime_error(msg.str());
    }

    return res;
  }

  template<>
  SignalState Parse<SignalState>(const std::string& src) {
    if( convertor.empty() ) {
      initconvertor();
    }

    try {
      SignalState sigState;
      sigState = convertor.right.at(src);
      return sigState;
    }
    catch( std::out_of_range& e ) {
      std::stringstream msg;
      msg << "Could not parse '";
      msg << src;
      msg << "' to SignalState";
      throw std::invalid_argument(msg.str());
    }
  }
}
