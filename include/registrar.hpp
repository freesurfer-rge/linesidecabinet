#pragma once

#include <map>
#include <string>

#include "linesideexceptions.hpp"

namespace Lineside {
  //! Class to register and retrieve items
  /*!
    This class wraps a `std::map` from `std::string` to raw pointers
    to the specified `ValueType`.
    Raw pointers are used because this class is for cases where
    ownership is retained elsewhere (such as hardware access which
    will be tied to the lifetime of some parent object).
    The returned pointers should only be used for accessing the
    target object, and not controlling its life.

    A further feature is that a given key may only be stored once.
    Any attempt to store the key again will result in a
    Lineside::DuplicateKeyException.
    Similarly, an attempt to retrieve a non-existent key will result
    in a Lineside::KeyNotFoundException.

    \tparam ValueType The type for which pointers will be stored
   */
  template<typename ValueType>
  class Registrar {
  public:
    Registrar() :
      store() {}

    //! Store the target pointer with the given key
    void Register( const std::string& name,
		   ValueType* target ) {
      if( this->store.count(name) != 0 ) {
	throw DuplicateKeyException(name);
      }
      this->store[name] = target;
    }

    //! Fetch the pointer corresponding to the given key
    ValueType* Retrieve( const std::string name ) const {
      if( this->store.count(name) != 1 ) {
	throw KeyNotFoundException(name);
      }
      return this->store.at(name);
    }
  private:
    std::map<std::string,ValueType*> store;
  };
}
