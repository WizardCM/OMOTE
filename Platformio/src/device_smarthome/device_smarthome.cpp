#include "commandHandler.h"
#include "device_smarthome/device_smarthome.h"

void register_device_smarthome() {
  #ifdef ENABLE_KEYBOARD_MQTT

  commands[SMARTHOME_MQTT_AIRCON_SETMODE] =      makeCommandData(MQTT, {"homeassistant/aircon/mode"});
  commands[SMARTHOME_MQTT_VRPC_WAKE] =           makeCommandData(MQTT, {"homeassistant/vr/wake"});
  commands[SMARTHOME_MQTT_TV_POWEROFF] =         makeCommandData(MQTT, {"homeassistant/tv/off"});
  commands[SMARTHOME_MQTT_TV_POWERON] =          makeCommandData(MQTT, {"homeassistant/tv/on"});
  commands[SMARTHOME_MQTT_TV_SETINPUT] =         makeCommandData(MQTT, {"homeassistant/tv/source"});
  commands[SMARTHOME_MQTT_XBOX_POWERON] =        makeCommandData(MQTT, {"homeassistant/xbox/on"});
  commands[SMARTHOME_MQTT_AIRCON_SETFAN] =       makeCommandData(MQTT, {"homeassistant/aircon/fan"});
  commands[SMARTHOME_MQTT_VRSENSORS_POWER] =     makeCommandData(MQTT, {"homeassistant/vrsensors/power"});
  commands[SMARTHOME_MQTT_BLINDSCOUCH_TOGGLE] =  makeCommandData(MQTT, {"homeassistant/blindscouch/toggle"});
  commands[SMARTHOME_MQTT_BLINDSWINDOW_SETPOS] = makeCommandData(MQTT, {"homeassistant/blindswindow/pos"});

  commands[SMARTHOME_MQTT_BULB1_SET]            = makeCommandData(MQTT, {"bulb1_set"             }); // payload must be set when calling commandHandler
  commands[SMARTHOME_MQTT_BULB2_SET]            = makeCommandData(MQTT, {"bulb2_set"             }); // payload must be set when calling commandHandler
  commands[SMARTHOME_MQTT_BULB1_BRIGHTNESS_SET] = makeCommandData(MQTT, {"bulb1_setbrightness"   }); // payload must be set when calling commandHandler
  commands[SMARTHOME_MQTT_BULB2_BRIGHTNESS_SET] = makeCommandData(MQTT, {"bulb2_setbrightness"   }); // payload must be set when calling commandHandler
  #endif
}
