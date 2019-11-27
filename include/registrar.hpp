#pragma once

#include <string>

#include "linesideexceptions.hpp"

namespace Lineside {
  template<typename StoredType>
  class Registrar {
  public:

    Registrar() :
      store() {}

    void Register( const std::string& name,
		   StoredType* target ) {
      this->store[name] = target;
    }

    StoredType* Retrieve( const std::string name ) const {
      if( this->store.count(name) != 1 ) {
	throw KeyNotFoundException(name);
      }
      return this->store.at(name);
    }
  private:
    std::map<std::string,StoredType*> store;
  };
}
