#pragma once

#include <vector>
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
      Listener(int reqSrcId, std::weak_ptr<Notifiable<bool>> l) :
	requestedSourceId(reqSrcId),
	listener(l) {}
      
      int requestedSourceId;
      std::weak_ptr<Notifiable<bool>> listener;
    };
    
    std::vector<Listener> listeners;
  };
}
