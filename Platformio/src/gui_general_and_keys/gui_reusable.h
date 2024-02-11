#include <lvgl.h>

lv_obj_t *add_ui_container(const char *label, int height, lv_obj_t *parent);

lv_obj_t *add_ui_button(const char *label, int width, int height, int x, int y, void *userdata, lv_obj_t *parent, lv_event_cb_t cb);

lv_obj_t *add_ui_slider(int width, int x, int y, int min, int max, int defaultValue, void *userdata, lv_obj_t *parent, lv_event_cb_t cb);

lv_obj_t *add_ui_toggle(const char *label, int x, int y, bool defaultState, void *userdata, bool notWrapped, lv_obj_t *parent, lv_event_cb_t cb);