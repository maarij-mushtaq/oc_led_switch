import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch
from esphome.const import CONF_ID, CONF_PIN

AUTO_LOAD = ["gpio"]  # ensure GPIO helpers are available

oc_ns = cg.esphome_ns.namespace('oc_led_switch')
OcLedSwitch = oc_ns.class_('OcLedSwitch', switch.Switch, cg.Component)

CONFIG_SCHEMA = switch.SWITCH_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(OcLedSwitch),
    cv.Required(CONF_PIN): cv.internal_gpio_output_pin_schema,
}).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield switch.register_switch(var, config)
    pin = yield cg.gpio_pin_expression(config[CONF_PIN])
    cg.add(var.set_pin(pin))
