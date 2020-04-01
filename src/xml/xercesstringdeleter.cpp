#include "xml/xercesstringdeleter.hpp"

namespace Lineside {
  namespace xml {
    void xercesstringdeleter::operator()( char* str ) {
      xercesc::XMLString::release( &str );
    }
  
    void xercesstringdeleter::operator()( XMLCh* str ) {
      xercesc::XMLString::release( &str );
    }
  }
}
