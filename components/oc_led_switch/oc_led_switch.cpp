#include "oc_led_switch.h"        // Our class declaration
#include "esphome/core/log.h"     // Logging macros (ESP_LOGCONFIG, LOG_PIN, LOG_SWITCH)

namespace esphome {
namespace oc_led_switch {

static const char *const TAG = "oc_led_switch";  // Prefix for our log lines

void OcLedSwitch::dump_config() {
  ESP_LOGCONFIG(TAG, "OC LED Switch:");     // Header line in logs
  LOG_SWITCH("", "Switch", this);           // Show generic switch info (name, state, etc.)
  if (pin_ != nullptr) {
    LOG_PIN("  Pin: ", pin_);               // Show which GPIO pin is used
  }
}

}  // namespace oc_led_switch
}  // namespace esphome
