#include <map>
#include "gui_general_and_keys/keys.h"
#include "device_samsungTV/device_samsungTV.h"
#include "device_yamahaAmp/device_yamahaAmp.h"
#include "device_denonAvr/device_denonAvr.h"
#include "device_smarthome/device_smarthome.h"
#include "scenes/sceneRegistry.h"
#include "scenes/scene_allOff.h"
#include "scenes/scene_TV.h"
#include "scenes/scene_fireTV.h"
#include "scenes/scene_chromecast.h"
#include "commandHandler.h"

std::map<char, repeatModes> key_repeatModes_TV {

  {'=', SHORT},          {'<', SHORT   },             {'p', SHORT         },         {'>', SHORT   },
  {'c', SHORT_REPEATED         },                                                                      {'i', SHORTorLONG         },
                                                {'u', SHORT_REPEATED},
                    {'l', SHORT_REPEATED},      {'k', SHORT},               {'r', SHORT_REPEATED},
                                                {'d', SHORT_REPEATED},
                    {'b', SHORT_REPEATED},                                                    {'s', SHORT_REPEATED         },
                                                                                              {'^', SHORT         },
                                                                                              {'v', SHORT         },

};

std::map<char, std::string> key_commands_short_TV {

  /* {'=', SAMSUNG_REWIND}, */      /* {'<', "DENON_INPUT_MEDIAPLAYER"},        {'p', "DENON_INPUT_GAME"}, */            {'>', DENON_INPUT_HEOS},
  {'c', SAMSUNG_INFO},                                                                        {'i', "SAMSUNG_KEYPAD"},
                                                {'u', SAMSUNG_UP},
                    {'l', SAMSUNG_LEFT},        {'k', SAMSUNG_SELECT},      {'r', SAMSUNG_RIGHT},
                                                {'d', SAMSUNG_DOWN},
         {'b', "SAMSUNG_RETURN2"},                                                                    {'s', "SAMSUNG_PLAYPAUSE_ALT"},
                                                                                               {'^', SAMSUNG_CHANNEL_UP},
                                                                                               {'v', SAMSUNG_CHANNEL_DOWN},

};

std::map<char, std::string> key_commands_long_TV {
  {'i', SAMSUNG_MENU}

};

void scene_start_sequence_TV(void) {
  executeCommand(SAMSUNG_POWER_ON);
  delay(100);
  std::string payload = "on";
  executeCommand(SMARTHOME_MQTT_TV_POWERON, payload);
  // executeCommand(YAMAHA_POWER_ON);
  // delay(1500);
  // executeCommand(YAMAHA_INPUT_DVD);
  // delay(3000);
  // executeCommand(SAMSUNG_INPUT_TV);
}

void scene_end_sequence_TV(void) {

}

std::string scene_name_TV = "TV";

void register_scene_TV(void){
  register_scene(
    scene_name_TV,
    & scene_start_sequence_TV,
    & scene_end_sequence_TV,
    & key_repeatModes_TV,
    & key_commands_short_TV,
    & key_commands_long_TV);

  commands[SCENE_TV]         = makeCommandData(SCENE, {scene_name_TV});
}
