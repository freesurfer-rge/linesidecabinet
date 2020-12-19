#pragma once

#include <stdexcept>
#include <sstream>

#include "lineside/itemid.hpp"
#include "lineside/signalstate.hpp"
#include "lineside/signalflash.hpp"

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
  class HardwareRequestException : public LinesideException {
  public:
    explicit HardwareRequestException(const std::string provider,
				      const std::string id,
				      const std::string issue) :
      LinesideException(""),
      providerName(provider),
      idOnProvider(id),
      issueDescription(issue),
      message() {
      std::stringstream tmp;
      tmp << "Bad Hardware Request for providerName "
	  << this->providerName
	  << " with idOnProvider "
	  << this->idOnProvider;
      tmp << ". Issue: "
	  << this->issueDescription;
      this->message = tmp.str();
    }

    const std::string providerName;
    const std::string idOnProvider;
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

  //! Exception for attempts set a bad state on a MultiAspectSignalHead
  class InvalidMASHStateException : public LinesideException {
  public:
    explicit InvalidMASHStateException(const ItemId targetItem,
				       const SignalState state,
				       const SignalFlash flash,
				       const unsigned int feather) :
      LinesideException(""),
      target(targetItem),
      state(state),
      flash(flash),
      feather(feather),
      message() {
      std::stringstream tmp;
      tmp << "Invalid state for " << this->target << ". ";
      tmp << "State was: "
	  <<  "{"
	  << state << ","
	  << flash << ","
	  << feather << "}";
      this->message = tmp.str();
    }
    
    const ItemId target;
    const SignalState state;
    const SignalFlash flash;
    const unsigned int feather;
    std::string message;

    virtual const char* what() const noexcept override {
      return this->message.c_str();
    }
  };
}
