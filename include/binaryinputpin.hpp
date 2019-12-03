#pragma once

#include <set>
#include <memory>

#include "notifiable.hpp"

namespace Lineside {
  //! Abstraction for a binary input pin
  /*!
    This class is more complex than Lineside::BinaryOutputPin since
    the program will have to respond to changes in the level.
   */
  class BinaryInputPin {
  public:
    
    BinaryInputPin() :
      listeners() {}
    
    virtual ~BinaryInputPin() {}

    //! Reads the current state of the pin
    virtual bool Get() const = 0;

    void RegisterListener(const int requestedSourceId,
			  std::weak_ptr<Notifiable<bool>> listener);
    
  protected:
    void NotifyUpdate();
    
  private:
    struct Listener {
      int requestedSourceId;
      std::weak_ptr<Notifiable<bool>> listener
    };
    
    std::set<Listener> listeners;
  };
}
