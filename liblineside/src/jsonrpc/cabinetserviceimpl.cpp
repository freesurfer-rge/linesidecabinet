#include <iostream>
#include "lineside/jsonrpc/cabinetserviceimpl.hpp"

namespace Lineside {
  namespace JsonRPC {
    
    CabinetServiceImpl::CabinetServiceImpl() {}
      
    CabinetServiceResponse
    CabinetServiceImpl::SetMultiAspectSignal(const Lineside::ItemId id,
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
    CabinetServiceImpl::SetMultiAspectSignalString(const std::string id,
						   const std::string state,
						   const std::string flash,
						   const unsigned int feather ) {
      auto idObj = Lineside::Parse<ItemId>(id);
      auto stateEnum = Lineside::Parse<Lineside::SignalState>(state);
      auto flashEnum = Lineside::Parse<Lineside::SignalFlash>(flash);
      return this->SetMultiAspectSignal(idObj, stateEnum, flashEnum, feather);
    }

    CabinetServiceResponse
    CabinetServiceImpl::SetTurnout(const Lineside::ItemId id,
				   const Lineside::TurnoutState state) {
      std::cout << __FUNCTION__ << ": "
		<< id << " "
		<< state << std::endl;
      
      return CabinetServiceResponse::Success;
    }

    CabinetServiceResponse
    CabinetServiceImpl::SetTurnoutString(const std::string id,
					 const std::string state) {
      auto idObj = Lineside::Parse<ItemId>(id);
      auto stateEnum = Lineside::Parse<Lineside::TurnoutState>(state);
      return this->SetTurnout(idObj, stateEnum);
    }

    bool CabinetServiceImpl::GetTrackCircuit(const Lineside::ItemId id) {
      std::cout << __FUNCTION__ << ": "
		<< id << std::endl;
      return true;
    }

    bool CabinetServiceImpl::GetTrackCircuitString(const std::string id) {
      auto idObj = Lineside::Parse<ItemId>(id);
      return this->GetTrackCircuit(idObj);
    }
  }
}
