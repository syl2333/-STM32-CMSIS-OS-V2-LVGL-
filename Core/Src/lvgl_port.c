#include "lvgl_port.h"

lv_disp_drv_t disp_drv; 
lv_indev_drv_t indev_drv;
static void disp_init(void);
static void indev_init(void);

static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);
static void indev_input_read(lv_indev_drv_t * drv, lv_indev_data_t*data);
void lv_port_disp_init(void)
{
	disp_init();
	
	
	static lv_disp_draw_buf_t disp_buf;
	static lv_color_t buf[2][480*135] __attribute__((at(Bank1_SRAM4_ADDR )));
	lv_disp_draw_buf_init(&disp_buf, buf[0],buf[1] , 480 * 135);
	
	//static lv_color_t buf[2][400*480] __attribute__((at(Bank1_SRAM4_ADDR)));
	//lv_disp_draw_buf_init(&disp_buf, buf[0], buf[1], 400 * 480);
	
	                       
	lv_disp_drv_init(&disp_drv); 

	disp_drv.hor_res = 480;
	disp_drv.ver_res = 800;
	
	disp_drv.flush_cb = disp_flush;
	
	disp_drv.draw_buf = &disp_buf;
	
	lv_disp_t* disp = lv_disp_drv_register(&disp_drv);
	lv_disp_set_default(disp);
	//lv_demo_benchmark();
	//lv_demo_music();
}

static void disp_init(void)
{
	hdma_memtomem_dma2_stream0.XferCpltCallback = lv_TransmitCpltCallback;
}


//LVGL使用DMA中断模式，向屏幕发送数据完成后的中断回调函数
void lv_TransmitCpltCallback( struct __DMA_HandleTypeDef * hdma)
{
	lv_disp_flush_ready(&disp_drv);
}

static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
	uint32_t length = (area->x2 - area->x1 + 1) * ( area->y2 - area->y1 + 1);
	NT35510_OpenWindow ( area->x1,  area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1);
	NT35510_Write_Cmd ( CMD_SetPixel );	
	HAL_DMA_Start_IT(&hdma_memtomem_dma2_stream0,(uint32_t)color_p,FSMC_Addr_NT35510_DATA,length);
	
}

void lv_port_indev_init(void)
{
	indev_init();
	
	lv_indev_drv_init(&indev_drv);
	
	indev_drv.type = LV_INDEV_TYPE_POINTER;
	indev_drv.read_cb = indev_input_read;
	
	
	lv_indev_drv_register(&indev_drv);
	
}

static void indev_init(void)
{
	GTP_Init_Panel();
}

extern int16_t lv_x,lv_y;
static void indev_input_read(lv_indev_drv_t * drv, lv_indev_data_t*data)
{
	if(lv_x != -1 || lv_y != -1)
	{
		data->point.x = lv_x;
		data->point.y = lv_y;
		data->state = LV_INDEV_STATE_PRESSED;
		
		data->continue_reading = false;
		
	}
	else
	{
		data->state = LV_INDEV_STATE_RELEASED; 
	}
}

//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{
//	if(GPIO_Pin == GPIO_PIN_8)
//	{
//		osEventFlagsSet(GT_Touch_ID,1);
//	}
//}
