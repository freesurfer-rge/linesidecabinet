#include <stdexcept>
#include <boost/bimap.hpp>

#include "pigpiodpp/gpiopull.hpp"

namespace PiGPIOdpp {
  static boost::bimap<GPIOPull,std::string> convertor;
  
  static void initconvertor() {
    typedef decltype(convertor)::value_type pos;
    convertor.insert( pos(GPIOPull::Off, "Off") );
    convertor.insert( pos(GPIOPull::Down, "Down") );
    convertor.insert( pos(GPIOPull::Up, "Up") );
  }
  
  std::ostream& operator<<( std::ostream& os, const GPIOPull p ) {
    os << ToString( p );
    return os;
  }
  
  std::string ToString( const GPIOPull p ) {
    if( convertor.empty() ) {
      initconvertor();
    }
    
    std::string res;
    try {
      res = convertor.left.at(p);
      }
    catch( std::out_of_range& e ) {
      std::stringstream msg;
      msg << "Unrecognised GPIOPull: ";
      msg << static_cast<int>(p);
      throw std::runtime_error(msg.str());
    }
    
    return res;
  }
  
  template<>
  GPIOPull Parse<GPIOPull>(const std::string& src) {
    if( convertor.empty() ) {
      initconvertor();
    }
    
    try {
      GPIOPull pull;
      pull = convertor.right.at(src);
      return pull;
    }
    catch( std::out_of_range& e ) {
      std::stringstream msg;
      msg << "Could not parse '";
      msg << src;
      msg << "' to GPIOPull";
      throw std::invalid_argument(msg.str());
    } 
  }
}

