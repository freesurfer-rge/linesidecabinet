#pragma once

#include <memory>
#include <vector>
#include <map>

#include "hardwaremanager.hpp"
#include "softwaremanager.hpp"
#include "itemid.hpp"
#include "pwitemcontroller.hpp"
#include "pwitemmodel.hpp"
#include "pwitemdata.hpp"

namespace Lineside {
  //! Class to manage permanent way items
  class PWItemManager {
  public:
    PWItemManager( std::shared_ptr<HardwareManager> hardwareManager,
		   std::shared_ptr<SoftwareManager> softwareManager )
      : hwManager(hardwareManager),
	swManager(softwareManager),
	pwItems() {}

    ~PWItemManager();

    void CreatePWItems( const std::vector<std::shared_ptr<PWItemData>>& itemData );

    std::weak_ptr<PWItemModel> GetPWItemModelById( const ItemId id ) const;

  private:
    std::shared_ptr<HardwareManager> hwManager;
    std::shared_ptr<SoftwareManager> swManager;
    std::map<ItemId,std::shared_ptr<PWItemController>> pwItems;
  };
}
