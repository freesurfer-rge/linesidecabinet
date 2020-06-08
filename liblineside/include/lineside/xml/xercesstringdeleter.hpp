#pragma once

#include <memory>

#include <xercesc/util/XMLString.hpp>

namespace Lineside {
  namespace xml {
    //! Deleter for use with xerces-allocated memory
    class xercesstringdeleter {
    public:
      void operator()( char* str );
      
      void operator()( XMLCh* str );
    };

    //! Shorthand for std::unique_ptr with a xercesstringdeleter
    template<typename T>
    using XercesPtr = typename std::unique_ptr<T,xercesstringdeleter>;

    //! Helper for creating a std::unique_ptr with a xercesdeleter
    template<typename T>
    std::unique_ptr<T,xercesstringdeleter> UniqueXercesPtr(T* ptr) {
      return std::unique_ptr<T,xercesstringdeleter>(ptr);
    }
  }
}
