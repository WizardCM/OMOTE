#include <map>
#include "gui_general_and_keys/keys.h"
#include "device_samsungTV/device_samsungTV.h"
#include "device_denonAvr/device_denonAvr.h"
#include "scenes/sceneRegistry.h"
#include "scenes/scene_allOff.h"
#include "scenes/scene_TV.h"
#include "scenes/scene_fireTV.h"
#include "scenes/scene_denonAvr.h"
#include "commandHandler.h"

std::map<char, repeatModes> key_repeatModes_denonAvr {

  /* {'=', SHORT}, */          {'<', SHORT   },             {'p', SHORT         },         {'>', SHORT   },
  {'c', SHORT},                                                                      {'i', SHORT},
                                                {'u', SHORT_REPEATED},
                    {'l', SHORT_REPEATED},      {'k', SHORT},               {'r', SHORT_REPEATED},
                                                {'d', SHORT_REPEATED},
                    {'b', SHORT},                                           {'s', SHORT},
              {'+', SHORT_REPEATED},                                           {'^', SHORT         },
              {'-', SHORT_REPEATED},           {'e', SHORT         },          {'v', SHORT         },
};

std::map<char, std::string> key_commands_short_denonAvr {
/* {'=', DENON_MED}, */      {'<', DENON_MEDIA_PREV},        {'p', DENON_MEDIA_PLAYPAUSE},            {'>', DENON_MEDIA_NEXT},
  {'c', DENON_OPTION},                                                              {'i', DENON_INFO},
                                                {'u', DENON_MENU_UP},
                    {'l', DENON_MENU_LEFT},        {'k', DENON_MENU_ENTER},      {'r', DENON_MENU_RIGHT},
                                                {'d', DENON_MENU_DOWN},
  {'b', DENON_BACK},                                                {'s', DENON_SETUP},
           {'+', DENON_VOL_PLUS},                                   {'^', DENON_CHAN_PLUS},
           {'-', DENON_VOL_MINUS},         {'e', DENON_VOL_MUTE},   {'v', DENON_CHAN_MINUS},
};

std::map<char, std::string> key_commands_long_denonAvr {


};

void scene_start_sequence_denonAvr(void) {

}

void scene_end_sequence_denonAvr(void) {

}

std::string scene_name_denonAvr = "Denon AVR";

void register_scene_denonAvr(void){
  register_scene(
    scene_name_denonAvr,
    & scene_start_sequence_denonAvr,
    & scene_end_sequence_denonAvr,
    & key_repeatModes_denonAvr,
    & key_commands_short_denonAvr,
    & key_commands_long_denonAvr);

  commands[SCENE_DENONAVR] = makeCommandData(SCENE, {scene_name_denonAvr});
}
