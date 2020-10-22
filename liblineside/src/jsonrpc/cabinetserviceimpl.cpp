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

    bool CabinetServiceImpl::GetTrackCircuit(const Lineside::ItemId id) {
      std::cout << __FUNCTION__ << ": "
		<< id << std::endl;
      Lineside::PWItemModel& item = this->pwim->GetPWItemModelById(id);
      Lineside::TrackCircuitMonitor& tcm = dynamic_cast<Lineside::TrackCircuitMonitor&>(item);
      return tcm.GetState();
    }
  }
}
