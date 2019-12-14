#pragma once

#include <stdexcept>
#include <sstream>

#include "itemid.hpp"

namespace Lineside {
  //! Base class for all exceptions from this library
  class LinesideException : public std::runtime_error {
  public:
    LinesideException(const std::string& what_arg ) : runtime_error(what_arg) {}
  };

  // ========================================

  //! Exception for mismatched ItemIds
  class ItemIdMismatchException : public LinesideException {
  public:
    explicit ItemIdMismatchException(const ItemId exp, const ItemId act) :
      LinesideException(""),
      expected(exp),
      actual(act),
      message() {
      std::stringstream tmp;
      tmp << "Expected " << this->expected;
      tmp << " but Got " << this->actual;
      this->message = tmp.str();
    }
    
    const ItemId expected;
    const ItemId actual;
    std::string message;

    virtual const char* what() const noexcept override {
      return this->message.c_str();
    }
  };

  // ========================================

  //! Base exception for problems with maps
  /*!
    This exception class is provided to allow
    failing operations on `std::map` objects
    to return the name of the offending key.
   */
  class KeyException : public LinesideException {
  public:
    //! The key which caused the exception
    const std::string keyName;

    virtual const char* what() const noexcept override {
      return this->message.c_str();
    }
  protected:
    explicit KeyException(const std::string& badKeyName) :
      LinesideException(""),
      keyName(badKeyName),
      message("MESSAGE NOT SET") {}

    std::string message;
  };

  //! Exception thrown if a given key is not found
  class KeyNotFoundException : public KeyException {
  public:
    explicit KeyNotFoundException(const std::string& badKeyName) :
      KeyException(badKeyName) {
      std::stringstream tmp;
      tmp << "Key '" << this->keyName << "' not found";
      this->message = tmp.str();
    }
  };

  //! Exception thrown if a key already exists in a map
  class DuplicateKeyException: public KeyException {
  public:
    explicit DuplicateKeyException(const std::string& badKeyName) :
      KeyException(badKeyName) {
      std::stringstream tmp;
      tmp << "Key '" << this->keyName << "' already present";
      this->message = tmp.str();
    }
  };
}
