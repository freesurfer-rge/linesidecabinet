#pragma once

#include <memory>

#include "tendril/hardwaremanager.hpp"
#include "mocks/mocksoftwaremanager.hpp"

struct MockManagerFixture {
  std::shared_ptr<Tendril::HardwareManager> hwManager;
  std::shared_ptr<MockSoftwareManager> swManager;

  MockManagerFixture() :
    hwManager(std::make_shared<Tendril::HardwareManager>()),
    swManager(std::make_shared<MockSoftwareManager>()) {
  }
};
