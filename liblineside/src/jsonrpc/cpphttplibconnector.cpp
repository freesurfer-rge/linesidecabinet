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

    CppHttpLibServerConnector::CppHttpLibServerConnector(jsonrpccxx::JsonRpcServer& server,
							 const std::string listenInterface,
							 const int port)
      : listenMtx(),
	thread(),
	server(server),
	httpServer(),
	listenInterface(listenInterface),
	port(port) {
      this->httpServer.Post(rpcPath.c_str(),
			    [this](const httplib::Request &req, httplib::Response &res) {
			      this->PostAction(req, res);
			    });
    }

    bool CppHttpLibServerConnector::StartListening() {
      std::lock_guard<std::mutex> lck(this->listenMtx);
      if (this->httpServer.is_running()) {
	  return false;
      }
      this->thread = std::thread([this]() {
				   this->httpServer.listen(this->listenInterface.c_str(), port);
				 });
      return true;
    }
      
    void CppHttpLibServerConnector::StopListening() {
      std::lock_guard<std::mutex> lck(this->listenMtx);
      if (this->httpServer.is_running()) {
	this->httpServer.stop();
	this->thread.join();
      }
    }

    void CppHttpLibServerConnector::PostAction(const httplib::Request &req,
					       httplib::Response &res) {
      res.status = 200;
      res.set_content(this->server.HandleRequest(req.body), rpcMIME.c_str());
    }
  }
}
