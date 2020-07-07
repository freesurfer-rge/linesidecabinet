#pragma once

#include <nlohmann/json.hpp>

#include "lineside/itemid.hpp"
#include "lineside/signalstate.hpp"

namespace Lineside {
  void to_json(nlohmann::json &j, const ItemId& id);
  void from_json(const nlohmann::json &j, Lineside::ItemId& id);

  NLOHMANN_JSON_SERIALIZE_ENUM(Lineside::SignalState,
			       {
				{Lineside::SignalState::Red, ToString(Lineside::SignalState::Red)},
				{Lineside::SignalState::Yellow, ToString(Lineside::SignalState::Yellow)},
				{Lineside::SignalState::DoubleYellow, ToString(Lineside::SignalState::DoubleYellow)},
				{Lineside::SignalState::Green, ToString(Lineside::SignalState::Green)}
			       });
}