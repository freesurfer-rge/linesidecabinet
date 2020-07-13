#include <iostream>
#include "lineside/jsonrpc/cabinetserviceimpl.hpp"

namespace Lineside {
  namespace JsonRPC {
    
    CabinetServiceImpl::CabinetServiceImpl() {}
      
    CabinetServiceResponse
    CabinetServiceImpl::SetMultiAspectSignal(const std::string id,
					     const Lineside::SignalState state,
					     const Lineside::SignalFlash flash,
					     const unsigned int feather) {
      std::cout << __FUNCTION__ << ": "
		<< id << " "
		<< state << " "
		<< flash << " "
		<< feather << std::endl;
      return CabinetServiceResponse::Success;
    }

    CabinetServiceResponse
    CabinetServiceImpl::SetTurnout(const std::string id,
				   const Lineside::TurnoutState state) {
      std::cout << __FUNCTION__ << ": "
		<< id << " "
		<< state << std::endl;
      
      return CabinetServiceResponse::Success;
    }

    bool CabinetServiceImpl::GetTrackCircuit(const std::string id) {
      Lineside::ItemId targetId;
      targetId.Parse(id);
      std::cout << __FUNCTION__ << ": "
		<< targetId << std::endl;
      return true;
    }
  }
}
