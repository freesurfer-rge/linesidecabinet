#pragma once

namespace Lineside {
  //! Abstraction for something which can receive notifications
  template<typename NotificationType>
  class Notifiable {
  public:
    //! Method to be called when some event occurs
    virtual void Notify(const int sourceId, const NotificationType notification) = 0;
  };
}
