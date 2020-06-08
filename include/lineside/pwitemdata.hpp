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

    //! Method to construct a permanent way item
    virtual
    std::shared_ptr<PWItemModel> Construct(HardwareManager& hw,
					   SoftwareManager& sw) const = 0;

  protected:
    //! Method for suppressing compiler warnings about unused SoftwareManager parameters
    void UnusedSoftwareManager(const SoftwareManager& sw) const;
  };
}
