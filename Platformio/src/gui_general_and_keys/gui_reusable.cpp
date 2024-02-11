#include "gui_general_and_keys/gui_reusable.h"
#include "gui_general_and_keys/guiBase.h"

lv_obj_t *add_ui_container(const char *label, int height, lv_obj_t *parent) {
  if (strlen(label) > 0) {
    lv_obj_t *heading = lv_label_create(parent);
    lv_label_set_text(heading, label);
  }

  lv_obj_t *menuBox = lv_obj_create(parent);
  lv_obj_set_size(menuBox, lv_pct(100), height);
  // lv_obj_set_style_bg_color(menuBox, color_primary, LV_PART_MAIN);
  lv_obj_set_style_border_width(menuBox, 0, LV_PART_MAIN);
  if (strlen(label) == 0) {
    lv_obj_set_style_pad_all(menuBox, 0, LV_PART_MAIN);
  } else {
    lv_obj_set_style_pad_bottom(menuBox, 0, LV_PART_MAIN);
  }

  return menuBox;
}

lv_obj_t *add_ui_button(const char *label, int width, int height, int x, int y, void *userdata, lv_obj_t *parent, lv_event_cb_t cb)
{
  lv_obj_t *button = lv_btn_create(parent);
  lv_obj_set_width(button, width);
  lv_obj_set_height(button, height);
  lv_obj_set_x(button, x);
  lv_obj_set_y(button, y);
  lv_obj_set_style_bg_color(button, color_primary, LV_PART_MAIN);
  lv_obj_set_style_radius(button, 14, LV_PART_MAIN);
  lv_obj_set_style_shadow_color(button, lv_color_hex(0x404040), LV_PART_MAIN);

  lv_obj_t *buttonLabel = lv_label_create(button);
  lv_label_set_text_fmt(buttonLabel, label);
  lv_obj_set_user_data(button, userdata);
  lv_obj_set_style_text_font(buttonLabel, &lv_font_montserrat_14, LV_PART_MAIN);
  lv_obj_center(buttonLabel);
  lv_obj_add_flag(buttonLabel, LV_OBJ_FLAG_EVENT_BUBBLE);

  lv_obj_add_event_cb(button, cb, LV_EVENT_CLICKED, NULL);

  return button;
}

lv_obj_t *add_ui_slider(int width, int x, int y, int min, int max, int defaultValue, void *userdata, lv_obj_t *parent, lv_event_cb_t cb) {

  lv_obj_t* slider = lv_slider_create(parent);
  lv_slider_set_range(slider, min, max);
  lv_obj_set_style_bg_color(slider, lv_color_lighten(lv_color_black(), 30), LV_PART_INDICATOR);
  lv_obj_set_style_bg_grad_color(slider, lv_color_lighten(lv_palette_main(LV_PALETTE_AMBER), 180), LV_PART_INDICATOR);
  lv_obj_set_style_bg_grad_dir(slider, LV_GRAD_DIR_HOR, LV_PART_INDICATOR);
  lv_obj_set_style_bg_color(slider, lv_color_white(), LV_PART_KNOB);
  lv_obj_set_style_bg_opa(slider, 255, LV_PART_MAIN);
  lv_obj_set_style_bg_color(slider, lv_color_lighten(color_primary, 50), LV_PART_MAIN);
  lv_slider_set_value(slider, defaultValue, LV_ANIM_OFF);
  lv_obj_set_size(slider, width, 10);
  lv_obj_align(slider, LV_ALIGN_TOP_MID, x, y);
  lv_obj_add_event_cb(slider, cb, LV_EVENT_RELEASED, userdata);

  return slider;
}

lv_obj_t *add_ui_toggle(const char *label, int x, int y, bool defaultState, void *userdata, bool notWrapped, lv_obj_t *parent, lv_event_cb_t cb) {

  int height = 22;
  lv_obj_t *wrapper = add_ui_container("", height, parent);
  lv_obj_set_pos(wrapper, x, y);
  if (notWrapped)
    lv_obj_set_style_bg_color(wrapper, lv_color_black(), LV_PART_MAIN);

  lv_obj_t* menuLabel = menuLabel = lv_label_create(wrapper);
  lv_label_set_text(menuLabel, label);
  lv_obj_align(menuLabel, LV_ALIGN_TOP_LEFT, 0, 3);

  lv_obj_t* toggle = lv_switch_create(wrapper);
  lv_obj_set_size(toggle, 40, height);
  lv_obj_align(toggle, LV_ALIGN_TOP_RIGHT, 0, 1);
  lv_obj_set_style_bg_color(toggle, lv_color_lighten(color_primary, 50), LV_PART_MAIN);
  lv_obj_set_style_bg_color(toggle, color_primary, LV_PART_INDICATOR);
  lv_obj_add_event_cb(toggle, cb, LV_EVENT_VALUE_CHANGED, userdata);

  return toggle;
}