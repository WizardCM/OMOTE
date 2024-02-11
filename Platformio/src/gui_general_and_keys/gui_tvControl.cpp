#include "commandHandler.h"
#include "device_denonAvr/device_denonAvr.h"
#include "device_samsungTV/device_samsungTV.h"
#include "device_smarthome/device_smarthome.h"
#include "gui_general_and_keys/guiBase.h"
#include "gui_general_and_keys/gui_reusable.h"
#include "gui_general_and_keys/guiRegistry.h"
#include "gui_general_and_keys/gui_tvControl.h"
#include "hardware/tft.h"
#include "scenes/sceneHandler.h"
#include "scenes/scene_TV.h"
#include <lvgl.h>


// Virtual Keypad Event handler
static void tvControlPanel_event_cb(lv_event_t *e) {
  lv_obj_t *target = lv_event_get_target(e);

  // send corrensponding number
  if (currentScene == scene_name_TV) {
    char *command = (char *)target->user_data;
    if (command == "APP_TWITCH") {
      executeCommand(SMARTHOME_MQTT_TV_SETINPUT, "Twitch");
    } else if (command == "APP_PLEX") {
      executeCommand(SMARTHOME_MQTT_TV_SETINPUT, "Plex");
    } else if (command == "APP_TUBI") {
      executeCommand(SMARTHOME_MQTT_TV_SETINPUT, "Tubi");
    } else if (strstr(command, "APP_") == command) {
      // TODO Not yet implemented
      return;
    } else {
      executeCommand(command);
    }
  }
}

void create_tab_content_tvControl(lv_obj_t* tab) {

  lv_obj_set_layout(tab, LV_LAYOUT_FLEX);
  lv_obj_set_flex_flow(tab, LV_FLEX_FLOW_COLUMN);

  lv_obj_t *wrapper;

  wrapper = add_ui_container("Other Sources", 86, tab);

  // int aThird = std::round(lv_obj_get_width(wrapper) / 3);
  // int aHalf = std::round(lv_obj_get_width(wrapper) / 2);
  int aThird = 64;
  int aHalf = 96;
  int buttonHeight = 30;
  int buttonSpacing = 2;

  int btn1x = -9;
  int btn2x = btn1x + aHalf + buttonSpacing;
  int btn2x3 = btn1x + aThird + buttonSpacing;
  int btn3x3 = btn1x + (aThird * 2) + (buttonSpacing * 2);

  int btnY = -9;

  add_ui_button("Switch",   aHalf, buttonHeight, btn1x, btnY,         (void *)"DENON_INPUT_AUX1",     wrapper, tvControlPanel_event_cb);
  add_ui_button("PS4",      aHalf, buttonHeight, btn2x, btnY,         (void *)"DENON_INPUT_AUX2",     wrapper, tvControlPanel_event_cb);
  // add_ui_button("BluTu",  aThird, buttonHeight, btn3x3, btnY,         (void *)"DENON_INPUT_BLUETOOTH", wrapper, tvControlPanel_event_cb);

  add_ui_button("Xbox 360", aHalf, buttonHeight, btn1x, buttonHeight, (void *)"DENON_INPUT_CABLESAT", wrapper, tvControlPanel_event_cb);
  add_ui_button("Wii",      aHalf, buttonHeight, btn2x, buttonHeight, (void *)"DENON_INPUT_BLURAY",   wrapper, tvControlPanel_event_cb);

  wrapper = add_ui_container("Applications", 86, tab);

  add_ui_button("Plex",    aThird, buttonHeight, btn1x, btnY,          (void *)"APP_PLEX",            wrapper, tvControlPanel_event_cb);
  add_ui_button("Twitch",  aThird, buttonHeight, btn2x3, btnY,         (void *)"APP_TWITCH",          wrapper, tvControlPanel_event_cb);
  add_ui_button("YouTube", aThird, buttonHeight, btn3x3, btnY,         (void *)"SAMSUNG_APP_YOUTUBE", wrapper, tvControlPanel_event_cb);

  add_ui_button("Tubi",    aThird, buttonHeight, btn1x,  buttonHeight, (void *)"APP_TUBI",            wrapper, tvControlPanel_event_cb);
  add_ui_button("Netflix", aThird, buttonHeight, btn2x3, buttonHeight, (void *)"SAMSUNG_APP_NETFLIX", wrapper, tvControlPanel_event_cb);
  add_ui_button("Prime",   aThird, buttonHeight, btn3x3, buttonHeight, (void *)"SAMSUNG_APP_PRIME",   wrapper, tvControlPanel_event_cb);

}

void notify_tab_before_delete_tvControl(void) {

}

void init_gui_pageIndicator_tvcontrol(lv_obj_t *panel) {
  // Create actual (non-clickable) buttons for every tab
  lv_obj_t *btn = lv_btn_create(panel);
  lv_obj_clear_flag(btn, LV_OBJ_FLAG_CLICKABLE);
  lv_obj_set_size(btn, 150, lv_pct(100));
  lv_obj_t *label = lv_label_create(btn);
  lv_label_set_text_fmt(label, "TV");
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_shadow_width(btn, 0, LV_PART_MAIN);
  lv_obj_set_style_bg_color(btn, color_primary, LV_PART_MAIN);
}

void register_gui_tvcontrol(void) {
  register_gui(std::string(tabName_tvControl), &create_tab_content_tvControl, &notify_tab_before_delete_tvControl);
}
