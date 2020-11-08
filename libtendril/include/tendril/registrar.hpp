#pragma once

#include <map>
#include <string>
#include <memory>

#include "tendril/keyexception.hpp"

namespace Tendril {
  //! Class to register and retrieve items
  /*!
    This class wraps a `std::map` from `std::string` to shared pointers
    to the specified `ValueType`.
    
    A further feature is that a given key may only be stored once.
    Any attempt to store the key again will result in a
    Tendril::DuplicateKeyException.
    Similarly, an attempt to retrieve a non-existent key will result
    in a Tendril::KeyNotFoundException.
    
    \tparam ValueType The type for which pointers will be stored
   */
  template<typename ValueType>
  class Registrar {
  public:
    Registrar() :
      store() {}

    //! Store the target pointer with the given key
    void Register( const std::string& name,
                   std::shared_ptr<ValueType> target ) {
      if( this->store.count(name) != 0 ) {
        throw DuplicateKeyException(name);
      }
      this->store[name] = target;
    }

    //! Fetch the pointer corresponding to the given key
    std::shared_ptr<ValueType> Retrieve( const std::string name ) const {
      if( this->store.count(name) != 1 ) {
        throw KeyNotFoundException(name);
      }
      return this->store.at(name);
    }
  private:
    std::map<std::string,std::shared_ptr<ValueType>> store;
  };
}
