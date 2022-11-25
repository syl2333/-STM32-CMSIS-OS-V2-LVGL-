#ifndef __LVGL_UI_H__
#define __LVGL_UI_H__

#include "lvgl.h"
#include "freertos.h"


void bg_test(void);
static void btn_clear_cb(lv_event_t* event);
void pedometer_cnt_fresh();
void heart_rate_fresh(int x);
void oxygen_rate_fresh(int x);
#endif
