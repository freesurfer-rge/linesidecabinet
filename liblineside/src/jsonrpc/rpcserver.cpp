#include "lineside/jsonrpc/jsonconvertors.hpp"

#include "lineside/jsonrpc/rpcserver.hpp"


namespace Lineside {
  namespace JsonRPC {
    RPCServer::RPCServer(std::shared_ptr<CabinetService> cabinet) :
      cabinet(cabinet),
      rpcServer() {
      // Due to difficulties handling custom types, need to use 'String' versions
      this->rpcServer.Add("SetMultiAspectSignal",
			  jsonrpccxx::GetHandle(&CabinetService::SetMultiAspectSignalString,
						*(this->cabinet.get())),
			  {"id", "state", "flash", "feather"});
      
      this->rpcServer.Add("SetTurnout",
			  jsonrpccxx::GetHandle(&CabinetService::SetTurnoutString,
						*(this->cabinet.get())),
			  {"id", "state"});
      
      this->rpcServer.Add("GetTrackCircuit",
			  jsonrpccxx::GetHandle(&CabinetService::GetTrackCircuitString,
						*(this->cabinet.get())),
			  {"id"});
    }
  }
}
