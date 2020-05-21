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

    virtual
    std::shared_ptr<PWItemModel> Construct(HardwareManager& hw,
					   SoftwareManager& sw) const = 0;

  protected:
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
    void UnusedSoftwareManager(const SoftwareManager& sw) const {
      // Do nothing
    }
#pragma clang diagnostic pop
  };
}
