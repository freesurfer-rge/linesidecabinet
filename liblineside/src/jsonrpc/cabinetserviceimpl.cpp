#include <iostream>

#include "lineside/multiaspectsignalhead.hpp"
#include "lineside/turnoutmotor.hpp"
#include "lineside/trackcircuitmonitor.hpp"

#include "lineside/jsonrpc/cabinetserviceimpl.hpp"

namespace Lineside {
  namespace JsonRPC {
    
    CabinetServiceImpl::CabinetServiceImpl(std::shared_ptr<const PWItemManager> itemManager)
      : pwim(itemManager) {}
      
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
      Lineside::PWItemModel& item = this->pwim->GetPWItemModelById(id);
      Lineside::MultiAspectSignalHead& mash = dynamic_cast<Lineside::MultiAspectSignalHead&>(item);
      mash.SetState(state, flash, feather);
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
      Lineside::PWItemModel& item = this->pwim->GetPWItemModelById(id);
      Lineside::TurnoutMotor& turnout = dynamic_cast<Lineside::TurnoutMotor&>(item);
      turnout.SetState(state);
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
      Lineside::PWItemModel& item = this->pwim->GetPWItemModelById(id);
      Lineside::TrackCircuitMonitor& tcm = dynamic_cast<Lineside::TrackCircuitMonitor&>(item);
      return tcm.GetState();
    }

    bool CabinetServiceImpl::GetTrackCircuitString(const std::string id) {
      auto idObj = Lineside::Parse<ItemId>(id);
      return this->GetTrackCircuit(idObj);
    }
  }
}
