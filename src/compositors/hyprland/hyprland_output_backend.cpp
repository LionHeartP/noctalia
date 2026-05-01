#include "compositors/hyprland/hyprland_config_backend.h"
#include "compositors/hyprland/hyprland_output_backend.h"

#include <format>
#include "core/process.h"

namespace compositors::hyprland {

  bool setOutputPower(bool on) {
    const std::string action = on ? "on" : "off";
    if (isLua()) {
      const std::string luaCmd = std::format("hl.dsp.dpms({{ action = \"{}\" }})", action);
      return process::runAsync({"hyprctl", "dispatch", luaCmd});
    }
    return process::runAsync({"hyprctl", "dispatch", "dpms", action});
  }

} // namespace compositors::hyprland
