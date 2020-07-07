#include <iostream>
#include <nlohmann/json.hpp>


#include "cabinetserver.hpp"

namespace Lineside {
  

inline void to_json (nlohmann::json &j, const Lineside::ItemId& id) {
  j = nlohmann::json{id.ToString()};
}
inline void from_json(const nlohmann::json &j, Lineside::ItemId& id) {
  id.Parse(j.get<std::string>());
}

NLOHMANN_JSON_SERIALIZE_ENUM(Lineside::SignalState,
			     {
			      {Lineside::SignalState::Red, ToString(Lineside::SignalState::Red)},
			      {Lineside::SignalState::Green, ToString(Lineside::SignalState::Green)}
			     });
    
}


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
