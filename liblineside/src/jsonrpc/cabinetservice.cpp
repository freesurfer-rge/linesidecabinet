#include <iostream>
#include "cabinetservice.hpp"


namespace Lineside {
  namespace JsonRPC {
    
    CabinetService::CabinetService() {}
      
    void CabinetService::SetMultiAspectSignal(const Lineside::ItemId id,
					      const Lineside::SignalState state,
					      const Lineside::SignalFlash flash,
					      const unsigned int feather) {
      std::cout << __FUNCTION__ << ": "
		<< id << " "
		<< state << " "
		<< flash << " "
		<< feather << std::endl;
    }

    void CabinetService::SetTurnout(const Lineside::ItemId id,
				    const Lineside::TurnoutState state) {
      std::cout << __FUNCTION__ << ": "
		<< id << " "
		<< state << std::endl;
    }
  }
}
