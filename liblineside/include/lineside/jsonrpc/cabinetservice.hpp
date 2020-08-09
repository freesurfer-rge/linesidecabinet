#pragma once

#include <functional>

#include "lineside/itemid.hpp"
#include "lineside/signalstate.hpp"
#include "lineside/signalflash.hpp"
#include "lineside/turnoutstate.hpp"

#include "lineside/jsonrpc/cabinetserviceresponse.hpp"

namespace Lineside {
  namespace JsonRPC {
    //! Interface for use by the RPC side
    class CabinetService {
    public:
      virtual ~CabinetService() {}

      //! Function to set the state of a multiaspect signal
      virtual
      CabinetServiceResponse
      SetMultiAspectSignal(const Lineside::ItemId id,
			   const Lineside::SignalState state,
			   const Lineside::SignalFlash flash,
			   const unsigned int feather) = 0;

      //! Function to set the state of a multiaspect signal
      /*!
	This is a dupicate with string arguments in case there are issues
	with converting the custom types.
       */
      virtual
      CabinetServiceResponse
      SetMultiAspectSignalString(const std::string id,
				 const std::string state,
				 const std::string flash,
				 const unsigned int feather) = 0;

      //! Function to set the state of a turnout
      virtual
      CabinetServiceResponse
      SetTurnout(const Lineside::ItemId id,
		 const Lineside::TurnoutState state) = 0;
      
      //! Function to set the state of a turnout
      /*!
	This is a dupicate with string arguments in case there are issues
	with converting the custom types.
       */
      virtual
      CabinetServiceResponse
      SetTurnoutString(const std::string id,
		       const std::string state) = 0;

      //! Function to get the state of a track circuit
      virtual bool GetTrackCircuit(const Lineside::ItemId id) = 0;

      //! Function to get the state of a track circuit
      /*!
	This is a dupicate with string arguments in case there are issues
	with converting the custom types.
       */
      virtual bool GetTrackCircuitString(const std::string id) = 0;
    };
  }
}
