#pragma once

#include <memory>

#include "itemid.hpp"
#include "pwitemmodel.hpp"
#include "hardwaremanager.hpp"
#include "softwaremanager.hpp"

namespace Lineside {
  //! Abstract base class for configuration data for permanent way items
  class PWItemData {
  public:
    PWItemData() : id(0) {}

    ItemId id;

    virtual ~PWItemData() {}

    virtual std::shared_ptr<PWItemModel> Construct( std::shared_ptr<HardwareManager> hw,
						    std::shared_ptr<SoftwareManager> sw ) const = 0;
  };
}
