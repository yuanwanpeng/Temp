/*
 * LCD12864_Display_Menu_Set_Time.c
 *
 *  Created on: 2018年10月22日
 *      Author: YuanWP
 */

#include "LCD12864_Display_Menu_Stroking_Cycle.h"
#include "button.h"
#include "HUMI.h"
#include "relay.h"
#include "string.h"
#include "LCD12864.h"

osThreadId Start_LCD12864_Stroking_Cycle_TaskHandle = NULL;

void LCD12864_Display_Stroking_Cycle_Interior(uint8_t* p_S_Stroking_Cycle)
{
	LCD12864_Put_16_16_Char(0xB5,0x14,0x04,WHITE_BASE);//行字
	LCD12864_Put_16_16_Char(0xB5,0x24,0x05,WHITE_BASE);//程字
	LCD12864_Put_16_16_Char(0xB5,0x34,0x15,WHITE_BASE);//周字
	LCD12864_Put_16_16_Char(0xB5,0x44,0x16,WHITE_BASE);//期字
	LCD12864_Put_8_16_Char(0xB5,0x54,':',WHITE_BASE);

	LCD12864_Display_Stroking_Cycle_Refresh(p_S_Stroking_Cycle);

}
void LCD12864_Display_Stroking_Cycle_Refresh(uint8_t* p_S_Stroking_Cycle)
{
	char Stroking_Cycle_arr[3];
	memset(Stroking_Cycle_arr,'0',sizeof(Stroking_Cycle_arr));

	sprintf(Stroking_Cycle_arr,"%02d",*p_S_Stroking_Cycle);

	LCD12864_Put_8_16_Char(0xB3,0x2a,Stroking_Cycle_arr[0],BLACK_BASE);
	LCD12864_Put_8_16_Char(0xB3,0x32,Stroking_Cycle_arr[1],BLACK_BASE);
	LCD12864_Put_16_16_Char(0xB3,0x3A,0x2A,WHITE_BASE);//秒
}
/*
 * 打印此界面
 * */
void LCD12864_Stroking_Cycle_Key_Null_Opt(uint8_t* p_S_Stroking_Cycle)
{
	LCD12864_Display_Stroking_Cycle_Interior(p_S_Stroking_Cycle);		//当前行程
}
void LCD12864_Display_Stroking_Cycle_Page(uint8_t key)
{
	static uint8_t S_Stroking_Cycle = 0;
	static uint8_t Mark = 0;
	osThreadId Old_Start_LCD12864_Stroking_Cycle_TaskHandle;
	if(Mark==0)
	{
		S_Stroking_Cycle = G_Stroking_Cycle;
		Mark = 1;
	}
	switch(key)
	{
	case NULL:	//第一次进入显示全部菜单内容
		LCD12864_Stroking_Cycle_Key_Null_Opt(&S_Stroking_Cycle);
		break;
	case K_1_num://选择按键
		LCD12864_Display_Stroking_Cycle_Refresh(&S_Stroking_Cycle);
		//G_Stroking_Cycle = S_Stroking_Cycle;
		Init_Stroking_Cycle(S_Stroking_Cycle);
		// 写入24c02
		break;
	case K_2_num:	//向上
		if(S_Stroking_Cycle<50)
		{
			S_Stroking_Cycle += 1;
			LCD12864_Display_Stroking_Cycle_Refresh(&S_Stroking_Cycle);
		}
		break;
	case K_3_num:	//向下
		if(S_Stroking_Cycle>3)
		{
			S_Stroking_Cycle -= 1;
			LCD12864_Display_Stroking_Cycle_Refresh(&S_Stroking_Cycle);
		}
		break;
	case K_4_num:	//
		if(Now_page == Stroking_Cycle_page){
			printf("now_page == Stroking_Cycle_page\r\n");
			//返回菜单界面
			LCD12864_Display(0x00,0x00);//清屏
			LCD12864_Display_Menu(NULL);
			S_Stroking_Cycle = G_Stroking_Cycle;
			Mark = 0;
			Now_page = Menu_Page;
			vTaskResume(Start_LCD12864_Menu_TaskHandle);//恢复挂起
			Old_Start_LCD12864_Stroking_Cycle_TaskHandle = Start_LCD12864_Stroking_Cycle_TaskHandle;
			Start_LCD12864_Stroking_Cycle_TaskHandle = NULL;
			osThreadTerminate(Old_Start_LCD12864_Stroking_Cycle_TaskHandle);

		}
		break;
	default:
		break;
	}
}

void Start_LCD12864_Stroking_Cycle_Task(void const * argument)
{
	BaseType_t err;
	uint32_t NotifyValue;
	LCD12864_Display(0x00,0x00);//清屏
	LCD12864_Display_Stroking_Cycle_Page(NULL);//第一次进入显示全部菜单内容
	while(1)
	{
		err = xTaskNotifyWait((uint32_t)0x00,	//2 等待按键信息
				(uint32_t)0xffffffff,
				(uint32_t*)&NotifyValue,
				(TickType_t)portMAX_DELAY);
		if(err==pdTRUE)
		{
			LCD12864_Display_Stroking_Cycle_Page((uint8_t)NotifyValue);
		}
	}
}

