#include "lvgl_ui.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"

static unsigned long cnt = 0;
LV_IMG_DECLARE(img_bg);
LV_FONT_DECLARE(font_xingkai_24);
lv_obj_t * label1;
lv_obj_t* heart_rate;
lv_obj_t* oxygen_rate;
void bg_test()
{
	lv_obj_t * img = lv_img_create(lv_scr_act());
	lv_img_set_src(img,&img_bg);
	lv_obj_set_pos(img,0,0);
	
	label1 = lv_label_create(lv_scr_act());
    lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);     /*Break the long lines*/
    lv_label_set_recolor(label1, true);                      /*Enable re-coloring by commands in the text*/
	lv_obj_set_style_text_font(label1,&font_xingkai_24,0);
	lv_label_set_text_fmt(label1, "#ffffff 当前步数为# #ff00ff ：# #ff0000 %d#",0);
	lv_obj_align(label1,LV_ALIGN_TOP_MID,-80,40);


	lv_obj_t * btn_cnt_clear = lv_btn_create(lv_scr_act());
	lv_obj_align(btn_cnt_clear,LV_ALIGN_TOP_MID,80,40);
	lv_obj_t * label_clear = lv_label_create(btn_cnt_clear);
	lv_label_set_text(label_clear,LV_SYMBOL_TRASH);
	//lv_obj_set_style_text_font(label_clear,&font_xingkai_24,0);
	lv_obj_add_event_cb(btn_cnt_clear,btn_clear_cb,LV_EVENT_CLICKED,NULL);
	
	
	heart_rate = lv_label_create(lv_scr_act());
	lv_obj_align(heart_rate,LV_ALIGN_TOP_MID,0,80);
	lv_obj_set_style_text_font(heart_rate,&font_xingkai_24,0);
	lv_label_set_text_fmt(heart_rate,"当前心率为：%d",0);
	
	oxygen_rate = lv_label_create(lv_scr_act());
	lv_obj_align(oxygen_rate,LV_ALIGN_TOP_MID,0,120);
	lv_obj_set_style_text_font(oxygen_rate,&font_xingkai_24,0);
	lv_label_set_text_fmt(oxygen_rate,"当前血氧为：%d",0);
}
static void btn_clear_cb(lv_event_t* event)
{
	dmp_set_pedometer_step_count(0);
}
void pedometer_cnt_fresh()
{
	dmp_get_pedometer_step_count(&cnt);
	lv_label_set_text_fmt(label1, "#ffffff 当前步数为# #ff00ff ：# #ff0000 %d#",(int)cnt);
}
void heart_rate_fresh(int x)
{
	lv_label_set_text_fmt(heart_rate,"当前心率为： %d",x);
}
void oxygen_rate_fresh(int x)
{
	lv_label_set_text_fmt(oxygen_rate,"当前血氧为： %d",x);
}