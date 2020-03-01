#pragma once

#include <memory>

#include "mocks/mockhardwaremanager.hpp"
#include "mocks/mocksoftwaremanager.hpp"

struct MockHardwareManagerFixture {
  std::shared_ptr<MockHardwareManager> hwManager;
  std::shared_ptr<MockSoftwareManager> swManager;

  MockHardwareManagerFixture() :
    hwManager(std::make_shared<MockHardwareManager>()),
    swManager(std::make_shared<MockSoftwareManager>()) {}
};
