#include "linesideexceptions.hpp"

#include "pwitemmanager.hpp"

namespace Lineside {
  PWItemManager::~PWItemManager() {
    for( auto kvPair=this->pwItems.begin(); kvPair!=this->pwItems.end(); ++kvPair ) {
      kvPair->second->Deactivate();
    }
  }
  
  void PWItemManager::CreatePWItems( const std::vector<std::shared_ptr<PWItemData>>& itemData ) {
    // Construct everything
    for( auto it=itemData.begin(); it!=itemData.end(); ++it ) {
      auto pwItemModel = (*it)->Construct( this->hwManager, this->swManager );

      auto pwItemController = PWItemController::Construct( pwItemModel );

      this->pwItems[pwItemModel->getId()] = pwItemController;
    }

    // Activate everything
    for( auto kvPair=this->pwItems.begin(); kvPair!=this->pwItems.end(); ++kvPair ) {
      kvPair->second->Activate();
    }
  }

  std::weak_ptr<PWItemModel> PWItemManager::GetPWItemModelById( const ItemId id ) const {
    if( this->pwItems.count(id) != 1 ) {
      throw KeyNotFoundException(id.ToString());
    }

    return this->pwItems.at(id)->GetModel();
  }
}
