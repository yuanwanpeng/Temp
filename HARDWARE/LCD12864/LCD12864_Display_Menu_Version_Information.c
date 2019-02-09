/*
 * LCD12864_Display_Menu_Set_Time.c
 *
 *  Created on: 2018年10月22日
 *      Author: YuanWP
 */

#include "LCD12864_Display_Menu_Set_Time.h"
#include "LCD12864_Display_Menu_Max_Route.h"
#include "LCD12864_Display_Menu_Route_Reset.h"
#include "button.h"
#include "HUMI.h"
#include "relay.h"
#include "string.h"
#include "LCD12864.h"
#include "LCD12864_Display_Menu_Set_Strategy.h"
#include "LCD12864_Display_Menu_HUMI_Compensation.h"

osThreadId Start_LCD12864_Set_Time_TaskHandle;

void LCD12864_Display_Set_Time_Interior(int8_t* p_S_comp)
{
	LCD12864_Put_16_16_Char(0xB5,0x14,0x0A,WHITE_BASE);//温字
	LCD12864_Put_16_16_Char(0xB5,0x24,0x0B,WHITE_BASE);//度字
	LCD12864_Put_16_16_Char(0xB5,0x34,0x0C,WHITE_BASE);//补字
	LCD12864_Put_16_16_Char(0xB5,0x44,0x0D,WHITE_BASE);//偿字
	LCD12864_Put_8_16_Char(0xB5,0x54,':',WHITE_BASE);

	LCD12864_Display_Set_Time_Refresh(p_S_comp);

}
void LCD12864_Display_Set_Time_Refresh(int8_t* p_S_comp)
{
	char comp_arr[5];
	memset(comp_arr,'0',sizeof(comp_arr));

		sprintf(comp_arr,"%03d",*p_S_comp);
		LCD12864_Put_8_16_Char(0xB3,0x2a,comp_arr[0],BLACK_BASE);
		LCD12864_Put_8_16_Char(0xB3,0x32,comp_arr[1],BLACK_BASE);
		LCD12864_Put_8_16_Char(0xB3,0x3a,'.',BLACK_BASE);
		LCD12864_Put_8_16_Char(0xB3,0x42,comp_arr[2],BLACK_BASE);

}
/*
 * 打印此界面
 * */
void LCD12864_Set_Time_Key_Null_Opt(int8_t* p_S_comp)
{
	LCD12864_Display_Set_Time_Interior(p_S_comp);		//当前行程
}
void LCD12864_Display_Set_Time_Page(uint8_t key)
{
	static int8_t S_comp = 0;
	static uint8_t Mark = 0;
	osThreadId Old_Start_LCD12864_Set_Time_TaskHandle;
	if(Mark==0)
	{
		S_comp = (int8_t)(comp*10);
		Mark = 1;
	}
	switch(key)
	{
	case NULL:	//第一次进入显示全部菜单内容
		LCD12864_Set_Time_Key_Null_Opt(&S_comp);
		break;
	case K_1_num://选择按键
		LCD12864_Display_Set_Time_Refresh(&S_comp);
		comp = ((float)S_comp)/10;
		break;
	case K_2_num:	//
		if(S_comp>(-50))
		{
			S_comp -= 1;
			LCD12864_Display_Set_Time_Refresh(&S_comp);
		}
		break;
	case K_3_num:	//
		if(S_comp<50)
		{
			S_comp += 1;
			LCD12864_Display_Set_Time_Refresh(&S_comp);
		}
		break;
	case K_4_num:	//
		if(Now_page == HUMI_Compensation_page){
			printf("now_page == HUMI_Compensation_page\r\n");
			//返回菜单界面
			LCD12864_Display(0x00,0x00);//清屏
			LCD12864_Display_Menu(NULL);
			S_comp = (int8_t)(comp*10);
			Mark = 0;
			Now_page = Menu_Page;
			vTaskResume(Start_LCD12864_Menu_TaskHandle);//恢复挂起
			Old_Start_LCD12864_Set_Time_TaskHandle = Start_LCD12864_Set_Time_TaskHandle;
			Start_LCD12864_Set_Time_TaskHandle = NULL;
			osThreadTerminate(Old_Start_LCD12864_Set_Time_TaskHandle);
		}
		break;
	default:
		break;
	}
}

void Start_LCD12864_HUMI_Compensation_Task(void const * argument)
{
	BaseType_t err;
	uint32_t NotifyValue;
	LCD12864_Display(0x00,0x00);//清屏
	LCD12864_Display_Set_Time_Page(NULL);//第一次进入显示全部菜单内容
	while(1)
	{
		err = xTaskNotifyWait((uint32_t)0x00,	//2 等待按键信息
				(uint32_t)0xffffffff,
				(uint32_t*)&NotifyValue,
				(TickType_t)portMAX_DELAY);
		if(err==pdTRUE)
		{
			LCD12864_Display_Set_Time_Page((uint8_t)NotifyValue);
		}
	}
}

