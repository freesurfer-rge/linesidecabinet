#pragma once

#include <stdexcept>
#include <sstream>

namespace Lineside {
  class LinesideException : public std::runtime_error {
  public:
    LinesideException(const std::string& what_arg ) : runtime_error(what_arg) {}
  };

  // ========================================

  class KeyException : public LinesideException {
  public:
    std::string keyName;

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
  
  class KeyNotFoundException : public KeyException {
  public:
    explicit KeyNotFoundException(const std::string& badKeyName) :
      KeyException(badKeyName) {
      std::stringstream tmp;
      tmp << "Key '" << this->keyName << "' not found";
      this->message = tmp.str();
    }
  };

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
