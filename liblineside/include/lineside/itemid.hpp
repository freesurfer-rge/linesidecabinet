#pragma once

#include <chrono>
#include <iostream>
#include <random>

#include "lineside/parse.hpp"

//! Namespace for this project
namespace Lineside {
  //! Class to hold an identifier for an item.
  /*!
    Internally, identifiers are held as integers, with this
    class providing conversions to and from strings.

    The string representations are of the form "hh:hh:hh:hh" were "h"
    represents some hexadecimal digit.
   */
  class ItemId {
  public:
    //! The internal representation type for the identifiers
    typedef uint32_t IdType;

    //! Default constructor
    ItemId() : id(0) {}

    //! Constructor for specified identifier value
    ItemId(IdType idVal) : id(idVal) {}

    //! Stores a copy of the identifier value in the given argument
    void Get(IdType* val) const {
      *val = this->id;
    }

    //! Returns the value of the identifier stored in this object
    /*!
      \return The content of this object
    */
    IdType Get() const {
      return this->id;
    }

    //! Sets the identifier stored in this object
    void Set(const IdType val) {
      this->id = val;
    }

    //! Parses a string and stores it in this object
    void Parse(std::string str);
    
    bool operator<(const ItemId item) const {
      return this->id < item.id;
    }

    bool operator==(const ItemId item) const {
      return this->id == item.id;
    }

    bool operator!=(const ItemId item) const {
      return !((*this)==item);
    }

    //! Convert to a string
    std::string ToString() const;

    //! Create a zero-valued id
    static ItemId Nil() {
      return ItemId();
    }

    //! Create a random id
    static ItemId Random() {
      unsigned long seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
      std::default_random_engine rand(seed);
      std::uniform_int_distribution<IdType> dist;

      return ItemId(dist(rand));
    }
  private:
    IdType id;
  };

  //! Stream insertion operator for Lineside::ItemId objects
  std::ostream& operator<<(std::ostream& os, const Lineside::ItemId& item);

  //! Stream extraction operator for Lineside::ItemId objects
  std::istream& operator>>(std::istream& is, Lineside::ItemId& item);

  //! Template specialisation for parsing
  template<>
  ItemId Parse<ItemId>(const std::string& src );
}


