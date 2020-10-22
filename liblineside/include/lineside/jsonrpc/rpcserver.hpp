#pragma once

#include "lineside/jsonrpc/cabinetservice.hpp"

#include <jsonrpccxx/server.hpp>

namespace Lineside {

  //! Ensure that the RPC server knows that ItemId can be got from a string
  constexpr nlohmann::json::value_t GetType(jsonrpccxx::type<ItemId>) {
    return nlohmann::json::value_t::string;
  }
  
  namespace JsonRPC {
    class RPCServer {
    public:
      RPCServer(std::shared_ptr<CabinetService> cabinet);

      jsonrpccxx::JsonRpc2Server& GetServer() {
	std::cerr << __FUNCTION__ << ": Needs better solution" << std::endl;
	return this->rpcServer;
      }
    private:
      std::shared_ptr<CabinetService> cabinet;
      jsonrpccxx::JsonRpc2Server rpcServer;
    };
  }
}
