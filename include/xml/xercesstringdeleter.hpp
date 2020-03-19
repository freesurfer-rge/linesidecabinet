#pragma once

#include <xercesc/util/XMLString.hpp>

namespace Lineside {
  namespace xml {
    class xercesstringdeleter {
    public:
      void operator()( char* str );
      
      void operator()( XMLCh* str );
    };
  }
}
