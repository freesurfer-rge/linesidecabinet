#pragma once

#include <memory>
#include <vector>
#include <map>

#include "lineside/hardwaremanager.hpp"
#include "lineside/softwaremanager.hpp"
#include "lineside/itemid.hpp"
#include "lineside/pwitemcontroller.hpp"
#include "lineside/pwitemmodel.hpp"
#include "lineside/pwitemdata.hpp"

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

    PWItemModel& GetPWItemModelById( const ItemId id ) const;

  private:
    std::shared_ptr<HardwareManager> hwManager;
    std::shared_ptr<SoftwareManager> swManager;
    std::map<ItemId,std::shared_ptr<PWItemController>> pwItems;
  };
}
