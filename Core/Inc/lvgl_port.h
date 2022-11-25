#ifndef __LVGL_PORT_H__
#define __LVGL_PORT_H__
#include "lvgl.h"
#include "cmsis_os.h"
#include "stm32f4xx.h"
#include "dma.h"
#include "bsp_nt35510_lcd.h"
#include "gt5xx.h"
#include "bsp_sdram.h"
#include "freertos.h"
#include "dma.h"
#include "lv_demo_benchmark.h"

extern int16_t pre_x[GTP_MAX_TOUCH];
extern int16_t pre_y[GTP_MAX_TOUCH];
extern osEventFlagsId_t GT_Touch_ID;

void lv_port_disp_init(void);
void lv_port_indev_init(void);
void lv_TransmitCpltCallback( struct __DMA_HandleTypeDef * hdma);
#endif
