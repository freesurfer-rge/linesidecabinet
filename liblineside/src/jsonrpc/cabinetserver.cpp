#include <iostream>
#include <nlohmann/json.hpp>

#include "lineside/jsonrpc/jsonconvertors.hpp"
#include "cabinetserver.hpp"


namespace Lineside {
  namespace JsonRPC {
    
    CabinetServer::CabinetServer() :
      rpcServer() {
      this->rpcServer.Add("SetMultiAspectSignal",
			  jsonrpccxx::GetHandle(&CabinetServer::SetMultiAspectSignal, *this),
			  {"id", "state", "flash", "feather"});
    }
      
    void CabinetServer::SetMultiAspectSignal(const Lineside::ItemId id,
					     const Lineside::SignalState state,
					     const Lineside::SignalFlash flash,
					     const unsigned int feather) {
      std::cout << __FUNCTION__ << ": "
		<< id << " "
		<< state << " "
		<< flash << " "
		<< feather << std::endl;
    }
  }
}
