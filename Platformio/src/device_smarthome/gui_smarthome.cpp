#include <string>
#include <lvgl.h>
#include "gui_general_and_keys/guiBase.h"
#include "gui_general_and_keys/guiRegistry.h"
#include "gui_general_and_keys/gui_reusable.h"
#include "hardware/tft.h"
#include "device_smarthome/device_smarthome.h"
#include "device_smarthome/gui_smarthome.h"
#include "commandHandler.h"
#include "scenes/sceneHandler.h"
#include "scenes/scene_TV.h"

// LVGL declarations
LV_IMG_DECLARE(lightbulb);

// static lv_obj_t* lightToggleA;
// static lv_obj_t* lightToggleB;
// static lv_obj_t* sliderA;
// static lv_obj_t* sliderB;
//
// static bool lightToggleAstate = false;
// static bool lightToggleBstate = false;
// static int32_t sliderAvalue = 0;
// static int32_t sliderBvalue = 0;

// Smart Home Toggle Event handler
static void smartHomeToggle_event_cb(lv_event_t * e){
  lv_obj_t *target = lv_event_get_target(e);
  Serial.println("Toggle hit");
  bool checked = lv_obj_has_state(target, LV_STATE_CHECKED);
  // Publish an MQTT message based on the event user data
  #if ENABLE_WIFI_AND_MQTT == 1
  char *cmd = (char *)e->user_data;
  Serial.print("User data read:");
  Serial.println(cmd);
  std::string command(cmd);
  Serial.println("Sending command");
  if (command.compare(SMARTHOME_MQTT_VRSENSORS_POWER) == 0) {
    Serial.println(command.c_str());
    executeCommand(command, checked ? "on" : "off");
    return;
  } else if (command.compare(SMARTHOME_MQTT_BLINDSCOUCH_TOGGLE) == 0) {
    Serial.println(command.c_str());
    executeCommand(command, checked ? "open" : "close");
    return;
  }
  #endif
}

// Smart Home Slider Event handler
static void smartHomeSlider_event_cb(lv_event_t* e){
  lv_obj_t * slider = lv_event_get_target(e);
  char payload[8];
  dtostrf(lv_slider_get_value(slider), 1, 2, payload);
  std::string payload_str(payload);
  char *cmd = (char *)e->user_data;
  std::string command(cmd);
  // Publish an MQTT message based on the event user data
  #if ENABLE_WIFI_AND_MQTT == 1
  if (command.compare(SMARTHOME_MQTT_BLINDSWINDOW_SETPOS) == 0) {
     executeCommand(command, payload);
     return;
  }
  #endif
}

static void smartHomePanel_event_cb(lv_event_t *e) {
  lv_obj_t *target = lv_event_get_target(e);
  // send corrensponding number
  if (currentScene == scene_name_TV) {
    char *cmd = (char *)target->user_data;
    std::string command(cmd);
  #if ENABLE_WIFI_AND_MQTT == 1
    if (command.rfind("AIRCON_MODE_", 0) == 0) {
      std::string cmdVal(command);
      cmdVal.replace(0, 12, "");
      executeCommand(SMARTHOME_MQTT_AIRCON_SETMODE, cmdVal);
      return;
    } else if (command.rfind("AIRCON_FAN_", 0) == 0) {
      std::string cmdVal(command);
      cmdVal.replace(0, 11, "");
      executeCommand(SMARTHOME_MQTT_AIRCON_SETFAN, cmdVal);
      return;
    }
  #endif
    executeCommand(command);
  }
}

void create_tab_content_smarthome(lv_obj_t* tab) {
  lv_obj_set_layout(tab, LV_LAYOUT_FLEX);
  lv_obj_set_flex_flow(tab, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_scrollbar_mode(tab, LV_SCROLLBAR_MODE_ACTIVE);

  lv_obj_t *wrapper;

  wrapper = add_ui_container("Air Conditioner", 83, tab);

  int aQuarter = 47;
  int buttonHeight = 30;
  int buttonSpacing = 2;

  int btn1x = -9;
  int btn2x = btn1x + aQuarter + buttonSpacing;
  int btn3x = btn1x + (aQuarter * 2) + (buttonSpacing * 2);
  int btn4x = btn1x + (aQuarter * 3) + (buttonSpacing * 3);

  int btnY = -9;

  add_ui_button("Heat", aQuarter, buttonHeight, btn1x, btnY, (void *)"AIRCON_MODE_heat", wrapper, smartHomePanel_event_cb);
  add_ui_button("Cool", aQuarter, buttonHeight, btn2x, btnY, (void *)"AIRCON_MODE_cool", wrapper, smartHomePanel_event_cb);
  add_ui_button("Fan",  aQuarter, buttonHeight, btn3x, btnY, (void *)"AIRCON_MODE_fan_only", wrapper, smartHomePanel_event_cb);
  add_ui_button("Off",  aQuarter, buttonHeight, btn4x, btnY, (void *)"AIRCON_MODE_off", wrapper, smartHomePanel_event_cb);

  int btnY2 = 30;

  add_ui_button("Quiet", aQuarter, buttonHeight, btn1x, btnY2, (void *)"AIRCON_FAN_Silent", wrapper, smartHomePanel_event_cb);
  add_ui_button("Low",   aQuarter, buttonHeight, btn2x, btnY2, (void *)"AIRCON_FAN_low", wrapper, smartHomePanel_event_cb);
  add_ui_button("Med",   aQuarter, buttonHeight, btn3x, btnY2, (void *)"AIRCON_FAN_medium", wrapper, smartHomePanel_event_cb);
  add_ui_button("High",  aQuarter, buttonHeight, btn4x, btnY2, (void *)"AIRCON_FAN_high", wrapper, smartHomePanel_event_cb);

  add_ui_toggle("VR Sensors", 0, 0, false, (void *)SMARTHOME_MQTT_VRSENSORS_POWER, true, tab, smartHomeToggle_event_cb);

  wrapper = add_ui_container("Blinds", 72, tab);

  add_ui_toggle("Couch", -2, -7, true, (void *)SMARTHOME_MQTT_BLINDSCOUCH_TOGGLE, false, wrapper, smartHomeToggle_event_cb);

  lv_obj_t *heading = lv_label_create(wrapper);
  int windowY = 26;
  lv_label_set_text(heading, "Window");
  lv_obj_set_x(heading, -2);
  lv_obj_set_y(heading, 26 + -4);

  add_ui_slider(lv_pct(60), 32, windowY, 0, 100, 100, (void *)SMARTHOME_MQTT_BLINDSWINDOW_SETPOS, wrapper, smartHomeSlider_event_cb);
}

/*void create_tab_content_smarthome2(lv_obj_t* tab) {

  // Add content to the smart home tab
  lv_obj_set_layout(tab, LV_LAYOUT_FLEX);
  lv_obj_set_flex_flow(tab, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_scrollbar_mode(tab, LV_SCROLLBAR_MODE_ACTIVE);

  // Add a label, then a box for the light controls
  lv_obj_t* menuLabel = lv_label_create(tab);
  lv_label_set_text(menuLabel, "Living Room");

  lv_obj_t* menuBox = lv_obj_create(tab);
  lv_obj_set_size(menuBox, lv_pct(100), 79);
  lv_obj_set_style_bg_color(menuBox, color_primary, LV_PART_MAIN);
  lv_obj_set_style_border_width(menuBox, 0, LV_PART_MAIN);

  lv_obj_t* bulbIcon = lv_img_create(menuBox);
  lv_img_set_src(bulbIcon, &lightbulb);
  lv_obj_set_style_img_recolor(bulbIcon, lv_color_white(), LV_PART_MAIN);
  lv_obj_set_style_img_recolor_opa(bulbIcon, LV_OPA_COVER, LV_PART_MAIN);
  lv_obj_align(bulbIcon, LV_ALIGN_TOP_LEFT, 0, 0);

  menuLabel = lv_label_create(menuBox);
  lv_label_set_text(menuLabel, "Floor Lamp");
  lv_obj_align(menuLabel, LV_ALIGN_TOP_LEFT, 22, 3);
  lightToggleA = lv_switch_create(menuBox);
  if (lightToggleAstate) {
    lv_obj_add_state(lightToggleA, LV_STATE_CHECKED);
  } else {
    // lv_obj_clear_state(lightToggleA, LV_STATE_CHECKED);
  }
  lv_obj_set_size(lightToggleA, 40, 22);
  lv_obj_align(lightToggleA, LV_ALIGN_TOP_RIGHT, 0, 0);
  lv_obj_set_style_bg_color(lightToggleA, lv_color_lighten(color_primary, 50), LV_PART_MAIN);
  lv_obj_set_style_bg_color(lightToggleA, color_primary, LV_PART_INDICATOR);
  lv_obj_add_event_cb(lightToggleA, smartHomeToggle_event_cb, LV_EVENT_VALUE_CHANGED, (void*)1);

  sliderA = lv_slider_create(menuBox);
  lv_slider_set_range(sliderA, 0, 100);
  lv_obj_set_style_bg_color(sliderA, lv_color_lighten(lv_color_black(), 30), LV_PART_INDICATOR);
  lv_obj_set_style_bg_grad_color(sliderA, lv_color_lighten(lv_palette_main(LV_PALETTE_AMBER), 180), LV_PART_INDICATOR);
  lv_obj_set_style_bg_grad_dir(sliderA, LV_GRAD_DIR_HOR, LV_PART_INDICATOR);
  lv_obj_set_style_bg_color(sliderA, lv_color_white(), LV_PART_KNOB);
  lv_obj_set_style_bg_opa(sliderA, 255, LV_PART_MAIN);
  lv_obj_set_style_bg_color(sliderA, lv_color_lighten(color_primary, 50), LV_PART_MAIN);
  lv_slider_set_value(sliderA, sliderAvalue, LV_ANIM_OFF);
  lv_obj_set_size(sliderA, lv_pct(90), 10);
  lv_obj_align(sliderA, LV_ALIGN_TOP_MID, 0, 37);
  lv_obj_add_event_cb(sliderA, smartHomeSlider_event_cb, LV_EVENT_VALUE_CHANGED, (void*)1);

  // Add another menu box for a second appliance
  menuBox = lv_obj_create(tab);
  lv_obj_set_size(menuBox, lv_pct(100), 79);
  lv_obj_set_style_bg_color(menuBox, color_primary, LV_PART_MAIN);
  lv_obj_set_style_border_width(menuBox, 0, LV_PART_MAIN);

  bulbIcon = lv_img_create(menuBox);
  lv_img_set_src(bulbIcon, &lightbulb);
  lv_obj_set_style_img_recolor(bulbIcon, lv_color_white(), LV_PART_MAIN);
  lv_obj_set_style_img_recolor_opa(bulbIcon, LV_OPA_COVER, LV_PART_MAIN);
  lv_obj_align(bulbIcon, LV_ALIGN_TOP_LEFT, 0, 0);

  menuLabel = lv_label_create(menuBox);
  lv_label_set_text(menuLabel, "Ceiling Light");
  lv_obj_align(menuLabel, LV_ALIGN_TOP_LEFT, 22, 3);
  lightToggleB = lv_switch_create(menuBox);
  if (lightToggleBstate) {
    lv_obj_add_state(lightToggleB, LV_STATE_CHECKED);
  } else {
    // lv_obj_clear_state(lightToggleB, LV_STATE_CHECKED);
  }
  lv_obj_set_size(lightToggleB, 40, 22);
  lv_obj_align(lightToggleB, LV_ALIGN_TOP_RIGHT, 0, 0);
  lv_obj_set_style_bg_color(lightToggleB, lv_color_lighten(color_primary, 50), LV_PART_MAIN);
  lv_obj_set_style_bg_color(lightToggleB, color_primary, LV_PART_INDICATOR);
  lv_obj_add_event_cb(lightToggleB, smartHomeToggle_event_cb, LV_EVENT_VALUE_CHANGED, (void*)2);

  sliderB = lv_slider_create(menuBox);
  lv_slider_set_range(sliderB, 0, 100);
  lv_obj_set_style_bg_color(sliderB, lv_color_lighten(lv_color_black(), 30), LV_PART_INDICATOR);
  lv_obj_set_style_bg_grad_color(sliderB, lv_color_lighten(lv_palette_main(LV_PALETTE_AMBER), 180), LV_PART_INDICATOR);
  lv_obj_set_style_bg_grad_dir(sliderB, LV_GRAD_DIR_HOR, LV_PART_INDICATOR);
  lv_obj_set_style_bg_color(sliderB, lv_color_white(), LV_PART_KNOB);
  lv_obj_set_style_bg_opa(sliderB, 255, LV_PART_MAIN);
  lv_obj_set_style_bg_color(sliderB, lv_color_lighten(color_primary, 50), LV_PART_MAIN);
  lv_slider_set_value(sliderB, sliderBvalue, LV_ANIM_OFF);
  lv_obj_set_size(sliderB, lv_pct(90), 10);
  lv_obj_align(sliderB, LV_ALIGN_TOP_MID, 0, 37);
  lv_obj_add_event_cb(sliderB, smartHomeSlider_event_cb, LV_EVENT_VALUE_CHANGED, (void*)2);


  // Add another room (empty for now)
  menuLabel = lv_label_create(tab);
  lv_label_set_text(menuLabel, "Kitchen");

  menuBox = lv_obj_create(tab);
  lv_obj_set_size(menuBox, lv_pct(100), 79);
  lv_obj_set_style_bg_color(menuBox, color_primary, LV_PART_MAIN);
  lv_obj_set_style_border_width(menuBox, 0, LV_PART_MAIN);

}*/

void notify_tab_before_delete_smarthome(void) {
  // remember to set all pointers to lvgl objects to NULL if they might be accessed from outside.
  // They must check if object is NULL and must not use it if so
  // lightToggleAstate = lv_obj_has_state(lightToggleA, LV_STATE_CHECKED);
  // lightToggleBstate = lv_obj_has_state(lightToggleB, LV_STATE_CHECKED);
  // sliderAvalue = lv_slider_get_value(sliderA);
  // sliderBvalue = lv_slider_get_value(sliderB);
}

void register_gui_smarthome(void){
  register_gui(std::string(tabName_smarthome), & create_tab_content_smarthome, & notify_tab_before_delete_smarthome);
}
