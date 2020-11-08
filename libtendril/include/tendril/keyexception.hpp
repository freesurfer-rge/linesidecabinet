#pragma once

#include <stdexcept>
#include <sstream>

namespace Tendril {
  //! Base class for errors with string-keyed maps
  class KeyException : public std::runtime_error {
  public:
    const std::string keyName;

    virtual const char* what() const noexcept override {
      return this->message.c_str();
    }

  protected:
    explicit KeyException(const std::string& name)
      : runtime_error(""),
	keyName(name),
	message("NOT SET") {}

    std::string message;
  };

  //! Exception thrown if given key is not found
  class KeyNotFoundException : public KeyException {
  public:
    explicit KeyNotFoundException(const std::string& name)
      : KeyException(name) {
      std::stringstream tmp;
      tmp << "Key '" << this->keyName << "' not found";
      this->message = tmp.str();
    }
  };

  //! Exception thrown if key already exists in a map
  class DuplicateKeyException : public KeyException {
  public:
    explicit DuplicateKeyException(const std::string& name)
      : KeyException(name) {
      std::stringstream tmp;
      tmp << "Key '" << this->keyName << "' already present";
      this->message = tmp.str();
    }
  };
}
