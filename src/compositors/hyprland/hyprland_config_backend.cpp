#include "compositors/hyprland/hyprland_config_backend.h"
#include "core/process.h"
#include <json.hpp>
#include <optional>

namespace compositors::hyprland {

  bool isLua() {
    static std::optional<bool> cachedIsLua;

    if (cachedIsLua.has_value()) {
      return *cachedIsLua;
    }

    const auto result = process::runSync({"hyprctl", "-j", "status"});

    if (result) {
      try {
        auto j = nlohmann::json::parse(result.out);
        cachedIsLua = (j.value("configProvider", "") == "lua");
      } catch (...) {
        return false;
      }
    }

    return cachedIsLua.value_or(false);
  }

} // namespace compositors::hyprland
