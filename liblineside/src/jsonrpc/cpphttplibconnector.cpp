#include "cpphttplibconnector.hpp"


namespace Lineside {
  namespace JsonRPC {

    const std::string rpcPath = "/jsonrpc";
    const std::string rpcMIME = "application/json";

    // =======================================
      
    std::string CppHttpLibClientConnector::Send(const std::string &request) {
      auto res = httpClient.Post(rpcPath.c_str(), request, rpcMIME.c_str());
      if (!res || res->status != 200) {
	throw jsonrpccxx::JsonRpcException(-32003, "client connector error, received status != 200");
      }
      return res->body;
    }

    // =======================================

    CppHttpLibServerConnector::CppHttpLibServerConnector(jsonrpccxx::JsonRpcServer &server,
							 int port)
      : server(server),
	port(port) {
      httpServer.Post(rpcPath.c_str(),
		      [&](const httplib::Request &req, httplib::Response &res) {
			this->PostAction(req, res);
		      });
    }


    void CppHttpLibServerConnector::PostAction(const httplib::Request &req,
					       httplib::Response &res) {
      res.status = 200;
      res.set_content(this->server.HandleRequest(req.body), rpcMIME.c_str());
    }
  }
}
