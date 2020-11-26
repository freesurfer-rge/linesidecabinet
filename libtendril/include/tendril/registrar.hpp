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

    While this is a very general concept, within Tendril it is used to
    provide access to various HardwareProvider classes.
    
    \tparam ValueType The type for which pointers will be stored. This is expected to be a HardwareProvider (although that is not technically required)
   */
  template<typename ValueType>
  class Registrar {
  public:
    Registrar() :
      store() {}

    //! Store the target pointer with the given key
    /*!
      An implementing library should make use of this method to populate the HardwareManager.

      @param name A string to identify the hardware provider
      @param target Pointer to the provider. This is a std::shared_ptr since some implementing classes may work with more than one Registrar (for example, a GPIO device can provide instances of both BinaryInputPin and BinaryOutputPin)
     */
    void Register( const std::string& name,
                   std::shared_ptr<ValueType> target ) {
      if( this->store.count(name) != 0 ) {
        throw DuplicateKeyException(name);
      }
      this->store[name] = target;
    }

    //! Fetch the pointer corresponding to the given key
    /*!
      A consuming library will use this to gain access to the HardwareProvider classes which it needs.

      @param name A string identifying the required provider
     */
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
