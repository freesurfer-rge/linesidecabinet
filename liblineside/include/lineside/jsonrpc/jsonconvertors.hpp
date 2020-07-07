#pragma once

#include <nlohmann/json.hpp>

#include "lineside/itemid.hpp"

namespace Lineside {
  void to_json(nlohmann::json &j, const ItemId& id);
  void from_json(const nlohmann::json &j, Lineside::ItemId& id);
}
