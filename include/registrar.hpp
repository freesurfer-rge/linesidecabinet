#pragma once

namespace Lineside {
  template<typename StoredType>
  class Registrar {
  public:

    Registrar() :
      store() {}

    void Register( const std::string& name,
		   StoredType& target ) {
      throw std::logic_error(__FUNCTION__);
    }

    StoredType& Retrieve( const std::string& name ) const {
      throw std::logic_error(__FUNCTION__);
    }
  private:
    std::map<std::string,StoredType&> store;
  };
}
