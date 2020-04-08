#include "pwitemmanager.hpp"

namespace Lineside {
  void PWItemManager::CreatePWItems( const std::vector<std::shared_ptr<PWItemData>>& itemData ) {
    if( itemData.size() == 0 ) {
      throw std::logic_error(__PRETTY_FUNCTION__);
    }
  }
}
