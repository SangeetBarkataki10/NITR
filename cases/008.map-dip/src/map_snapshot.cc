#include "map_snapshot.h"

#include <stdexcept>

#include "providers_builtin.h"

namespace nitr::case008 {

std::unique_ptr<ILayerProvider> MapSnapshotService::CreateProviderHardcoded(
    const nlohmann::json& layer_json) const {
  if (!layer_json.is_object() || !layer_json.contains("type") ||
      !layer_json["type"].is_string()) {
    throw std::runtime_error(
        "each layer must be an object with string field 'type'");
  }
  const std::string type = layer_json["type"].get<std::string>();

  // STARTER DIP violation: hardcoded branching on concrete types.
  if (type == "geometry") {
    return std::make_unique<GeometryProvider>();
  }
  if (type == "semantics") {
    return std::make_unique<SemanticsProvider>();
  }

  throw std::runtime_error("unknown layer type: " + type);
}

std::string MapSnapshotService::BuildSnapshot(
    const nlohmann::json& config, const std::string& payload) const {
  if (!config.is_object() || !config.contains("layers") ||
      !config["layers"].is_array()) {
    throw std::runtime_error(
        "config must be an object with array field 'layers'");
  }

  // Output format (stable for tests):
  // SNAPSHOT
  // <layer_name>:<layer_value>
  // ...
  std::string out = "SNAPSHOT\n";
  for (const auto& layer_json : config["layers"]) {
    std::unique_ptr<ILayerProvider> p = CreateProviderHardcoded(layer_json);
    out += p->Name();
    out += ":";
    out += p->BuildLayer(payload);
    out += "\n";
  }
  return out;
}

}  // namespace nitr::case008
