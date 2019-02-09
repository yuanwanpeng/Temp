/*
 * LCD12864_Display_Menu.h
 *
 *  Created on: 2018��9��13��
 *      Author: YuanWP
 */

#ifndef HARDWARE_LCD12864_LCD12864_DISPLAY_MENU_H_
#define HARDWARE_LCD12864_LCD12864_DISPLAY_MENU_H_
#include "main.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "stdint.h"
#include "LCD12864.h"
#define MENU_LINE 8			//���˵�ѡ����Ŀ����
#define MENU_LINE_MIN	0	//

#define BLACK_BASE 1
#define WHITE_BASE 0

#define Up_Page 10
#define Next_Page 11

#define THIS_LINE 0
#define SUB_LINE 1
#define ADD_LINE 2

extern osThreadId Start_LCD12864_HUMI_TaskHandle;
extern osThreadId Start_LCD12864_Menu_TaskHandle;
typedef enum
{
	Set_Strategy = 0,	//��������
	Route_Reset,		//�г̹���
	Max_Route,			//����г�
	HUMI_Compensation,	//�¶Ȳ���
	Delay_inspection,	//��ʱ���
	Set_Time,			//ʱ��У׼
	Stroking_Cycle,		//�г�����
	Version_Information,//�汾��Ϣ
}option;
typedef enum
{
	At_Null = -1,
	Route_Reset_Item = 0,
	Max_Route_Item,
	HUMI_Compensation_Item,
}Item_Menu;

void LCD12864_Display_Menu(uint8_t key);

void Dispose_Function_Key(option* p_this_line,Item_Menu* p_now_opt_select);
void LCD12864_Key_Null_Opt(option* p_this_line,uint8_t* p_page,Item_Menu* p_now_opt_select);

void LCD12864_Display_Menu_Is_Route_Reset(uint8_t opt,option* p_this_line,Item_Menu* p_now_opt_select);

void Start_LCD12864_Display_Menu_Task(void const * argument);
void LCD12864_Display_Menu_Option_Refresh(option* this_line,uint8_t opt);

void LCD12864_Display_Set_Strategy(option* this_line);
void LCD12864_Display_Route_Reset(option* this_line);
void LCD12864_Display_Max_Route(option* this_line);
void LCD12864_Display_HUMI_Compensation(option* this_line);
void LCD12864_Display_Delay_inspection(option* this_line);
void LCD12864_Display_Set_Time(option* this_line);
void LCD12864_Display_Stroking_Cycle(option* this_line);
void LCD12864_Display_Version_Information(option* this_line);

#endif /* HARDWARE_LCD12864_LCD12864_DISPLAY_MENU_H_ */







