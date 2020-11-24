#pragma once

#include <memory>

#include "tendril/hardwaremanager.hpp"
#include "tendril/mocks/utilities.hpp"
#include "mocks/mocksoftwaremanager.hpp"

struct MockManagerFixture {
  std::shared_ptr<Tendril::HardwareManager> hwManager;
  std::shared_ptr<MockSoftwareManager> swManager;

  MockManagerFixture() :
    hwManager(Tendril::Mocks::GetMockHardwareManager()),
    swManager(std::make_shared<MockSoftwareManager>()) {
  }
};
