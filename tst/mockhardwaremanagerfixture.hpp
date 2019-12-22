#pragma once

#include <memory>

#include "mocks/mockhardwaremanager.hpp"

struct MockHardwareManagerFixture {
  std::shared_ptr<MockHardwareManager> hwManager;

  MockHardwareManagerFixture() :
    hwManager(std::make_shared<MockHardwareManager>()) {}
};
