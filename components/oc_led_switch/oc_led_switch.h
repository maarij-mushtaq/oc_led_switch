#pragma once  // Avoid multiple inclusion of this header

// Bring in ESPHome base classes and GPIO helpers.
#include "esphome/core/component.h"            // Component: gives setup(), dump_config()
#include "esphome/components/switch/switch.h"  // Switch: gives write_state(), publish_state()
#include "esphome/components/gpio/gpio.h"      // GPIOPin abstraction (setup, digital_write)

namespace esphome {
namespace oc_led_switch {

// A switch that toggles a GPIO pin (e.g., LED on GPIO14)
class OcLedSwitch : public switch_::Switch, public Component {
 public:
  // Called from Python glue to pass a configured pin into this class
  void set_pin(gpio::GPIOPin *pin) { pin_ = pin; }

  // Runs once at boot
  void setup() override {
    pin_->setup();               // configure pin using the mode from YAML (OUTPUT)
    pin_->digital_write(false);  // start OFF (LOW). Flip in YAML with 'inverted: true' if needed.
  }

  // Pretty-print configuration to logs at startup
  void dump_config() override;

 protected:
  // Called whenever HA/ESPHome toggles the switch
  void write_state(bool state) override {
    pin_->digital_write(state);  // drive pin HIGH/LOW
    this->publish_state(state);  // report new state back to ESPHome/HA/MQTT
  }

  gpio::GPIOPin *pin_{nullptr};  // we store the pin object here
};

}  // namespace oc_led_switch
}  // namespace esphome
