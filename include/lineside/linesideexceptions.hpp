#pragma once

#include <stdexcept>
#include <sstream>

#include "lineside/itemid.hpp"

namespace Lineside {
  //! Base class for all exceptions from this library
  class LinesideException : public std::runtime_error {
  public:
    LinesideException(const std::string& what_arg ) : runtime_error(what_arg) {}
  };

  // ========================================

  //! Exception for failure to lock a std::weak_ptr
  class PointerLockFailureException : public LinesideException {
  public:
    explicit PointerLockFailureException(const std::string file, const unsigned int line) :
      LinesideException(""),
      filename(file),
      linenumber(line),
      message() {
      std::stringstream tmp;
      tmp << "Failed to lock weak_ptr at line "
	  << this->linenumber
	  << " of file "
	  << this->filename;
      this->message = tmp.str();
    }

    const std::string filename;
    const unsigned int linenumber;
    std::string message;
    
    virtual const char* what() const noexcept override {
      return this->message.c_str();
    }
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

  //! Exception for bad PWItem data
  class BadPWItemDataException : public LinesideException {
  public:
    explicit BadPWItemDataException(const ItemId target, const std::string info) :
      LinesideException(""),
      item(target),
      message() {
      std::stringstream tmp;
      tmp << "Configuration problem for " << this->item;
      tmp << " - " << info;
      this->message = tmp.str();
    }
    
    const ItemId item;
    std::string message;

    virtual const char* what() const noexcept override {
      return this->message.c_str();
    }
  };

  // ========================================

  //! Exception for improper hardware requests
  /*!
    Hardware manager implementations throw this
    when unable to satisfy a device request
   */
  class DeviceRequestException : public LinesideException {
  public:
    explicit DeviceRequestException(const std::string ctrl,
				    const std::string ctrlData,
				    const std::string issue) :
      LinesideException(""),
      controller(ctrl),
      controllerData(ctrlData),
      issueDescription(issue),
      message() {
      std::stringstream tmp;
      tmp << "Bad Device Request for controller "
	  << this->controller
	  << " with controllerData "
	  << this->controllerData;
      tmp << ". Issue: "
	  << this->issueDescription;
      this->message = tmp.str();
    }

    const std::string controller;
    const std::string controllerData;
    const std::string issueDescription;
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

  // ========================================

  //! Exception for attempts to place PWItem into invalid state
  class InvalidStateException : public LinesideException {
  public:
    explicit InvalidStateException(const ItemId targetItem, const std::string stateInfo) :
      LinesideException(""),
      target(targetItem),
      info(stateInfo),
      message() {
      std::stringstream tmp;
      tmp << "Invalid state for " << this->target << ".";
      tmp << " State was: " << this->info;
      this->message = tmp.str();
    }
    
    const ItemId target;
    const std::string info;
    std::string message;

    virtual const char* what() const noexcept override {
      return this->message.c_str();
    }
  };
}
