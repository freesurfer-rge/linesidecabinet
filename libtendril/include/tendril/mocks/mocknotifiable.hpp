#pragma once

#include "tendril/notifiable.hpp"

namespace Tendril {
  namespace Mocks {
    template<typename T>
    class MockNotifiable : public Notifiable<T> {
    public:
      MockNotifiable() :
	Notifiable<T>(),
	lastNotification() {}
      
      virtual void Notify(const T& notification) override {
	this->lastNotification = notification;
      }
      
      T lastNotification;
    };
  }
}
