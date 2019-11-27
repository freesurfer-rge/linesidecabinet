#pragma once

#include <stdexcept>
#include <sstream>

namespace Lineside {
  class LinesideException : public std::runtime_error {
  public:
    LinesideException(const std::string& what_arg ) : runtime_error(what_arg) {}
  };

  // ========================================

  class KeyNotFoundException : public LinesideException {
  public:
    explicit KeyNotFoundException(const std::string& badKeyName) :
      LinesideException(""),
      badKey(badKeyName),
      message() {
      std::stringstream tmp;
      tmp << "Key '" << this->badKey << "' not found";
      this->message = tmp.str();
    }

    virtual const char* what() const noexcept override {
      return this->message.c_str();
    }
    
    std::string badKey;
  private:
    std::string message;
  };
}
