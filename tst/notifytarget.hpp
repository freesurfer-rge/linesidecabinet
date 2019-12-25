#include "notifiable.hpp"

class NotifyTarget : public Lineside::Notifiable<bool> {
public:
  NotifyTarget() :
    lastNotificationSource(0),
    lastNotification(false) {}
  
  unsigned int lastNotificationSource;
  bool lastNotification;

  virtual void Notify(const unsigned int sourceId, const bool notification) override {
    this->lastNotificationSource = sourceId;
    this->lastNotification = notification;
  }
};
