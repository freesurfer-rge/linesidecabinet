#pragma once

#include <memory>

#include "itemid.hpp"
#include "pwitemmodel.hpp"
#include "hardwaremanager.hpp"

namespace Lineside {
  class PWItemData {
  public:
    PWItemData() : id(0) {}

    ItemId id;

    virtual ~PWItemData() {}

    virtual std::shared_ptr<PWItemModel> Construct( std::shared_ptr<HardwareManager> hw ) = 0;
  };
}
