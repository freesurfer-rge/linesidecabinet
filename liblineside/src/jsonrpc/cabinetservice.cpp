#include <iostream>
#include "lineside/jsonrpc/cabinetservice.hpp"


namespace Lineside {
  namespace JsonRPC {
    
    CabinetService::CabinetService() {}
      
    bool CabinetService::SetMultiAspectSignal(const std::string id,
					      const Lineside::SignalState state,
					      const Lineside::SignalFlash flash,
					      const unsigned int feather) {
      std::cout << __FUNCTION__ << ": "
		<< id << " "
		<< state << " "
		<< flash << " "
		<< feather << std::endl;
      return true;
    }

    bool CabinetService::SetTurnout(const std::string id,
				    const Lineside::TurnoutState state) {
      std::cout << __FUNCTION__ << ": "
		<< id << " "
		<< state << std::endl;

      return true;
    }

    bool CabinetService::GetTrackCircuit(const std::string id) {
      Lineside::ItemId targetId;
      targetId.Parse(id);
      std::cout << __FUNCTION__ << ": "
		<< targetId << std::endl;
      return true;
    }
  }
}
