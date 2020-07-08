#include "lineside/jsonrpc/jsonconvertors.hpp"

namespace Lineside {
  void to_json (nlohmann::json &j, const ItemId& id) {
    j = id.ToString();
  }
  
  void from_json(const nlohmann::json &j, Lineside::ItemId& id) {
    id.Parse(j.get<std::string>());
  }
}
