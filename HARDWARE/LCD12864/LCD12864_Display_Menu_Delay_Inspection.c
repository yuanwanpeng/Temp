/*
 * LCD12864_Display_Menu_Delay_Inspection.c
 *
 *  Created on: 2018��10��22��
 *      Author: YuanWP
 */
#include "LCD12864_Display_Menu_Max_Route.h"
#include "LCD12864_Display_Menu_Route_Reset.h"
#include "button.h"
#include "HUMI.h"
#include "relay.h"
#include "string.h"
#include "LCD12864.h"
#include "LCD12864_Display_Menu_Set_Strategy.h"
#include "LCD12864_Display_Menu_Delay_Inspection.h"
osThreadId Start_LCD12864_Delay_Inspection_TaskHandle;

void LCD12864_Display_Delay_Inspection_Interior(uint8_t* p_S_Delay_Inspection,uint8_t* p_Coordinate)
{
	LCD12864_Put_16_16_Char(0xB7,0x14,0x0E,WHITE_BASE);//����
	LCD12864_Put_16_16_Char(0xB7,0x24,0x0F,WHITE_BASE);//ʱ��
	LCD12864_Put_16_16_Char(0xB7,0x34,0x10,WHITE_BASE);//����
	LCD12864_Put_16_16_Char(0xB7,0x44,0x11,WHITE_BASE);//����
	LCD12864_Put_8_16_Char(0xB7,0x54,':',WHITE_BASE);

	LCD12864_Display_Delay_Inspection_Refresh(p_S_Delay_Inspection,p_Coordinate);

	LCD12864_Put_16_16_Char(0xB5,0x52,0x28,WHITE_BASE);//����
	LCD12864_Put_16_16_Char(0xB5,0x62,0x29,WHITE_BASE);//����
 
	LCD12864_Put_16_16_Char(0xB3,0x14,0x02,WHITE_BASE);//����
	LCD12864_Put_16_16_Char(0xB3,0x24,0x03,WHITE_BASE);//����
}
void LCD12864_Display_Delay_Inspection_Refresh(uint8_t* p_S_Delay_Inspection,uint8_t* p_Coordinate)
{
	char Delay_Inspection_arr[2];
	memset(Delay_Inspection_arr,'0',sizeof(Delay_Inspection_arr));
	sprintf(Delay_Inspection_arr,"%d",*p_S_Delay_Inspection);

	LCD12864_Put_8_16_Char(0xB5,0x3a,Delay_Inspection_arr[0],(*p_Coordinate)==0);

	LCD12864_Put_16_16_Char(0xB3,0x14,0x02,(*p_Coordinate)==1);//����
	LCD12864_Put_16_16_Char(0xB3,0x24,0x03,(*p_Coordinate)==1);//����
}
/*
 * ��ӡ�˽���
 * */
void LCD12864_Delay_Inspection_Key_Null_Opt(uint8_t* p_S_Delay_Inspection,uint8_t* p_Coordinate)
{
	LCD12864_Display_Delay_Inspection_Interior(p_S_Delay_Inspection,p_Coordinate);		//��ǰ�г�
}
void LCD12864_Display_Delay_Inspection_Page(uint8_t key)
{
	static uint8_t S_Delay_Inspection = 0;
	static uint8_t Mark = 0;
	static uint8_t S_Coordinate = 0;//��ǰ����
	if(Mark==0)
	{
		S_Delay_Inspection = G_Delay_Inspection;
		Mark = 1;
	}
	switch(key)
	{
	case NULL:	//��һ�ν�����ʾȫ���˵�����
		LCD12864_Delay_Inspection_Key_Null_Opt(&S_Delay_Inspection,&S_Coordinate);
		break;
	case K_1_num://ѡ�񰴼�
//		LCD12864_Display_Delay_Inspection_Refresh(&S_Delay_Inspection);
//		G_Delay_Inspection = S_Delay_Inspection;
//		Init_Delay_Inspection(G_Delay_Inspection);
		if(S_Coordinate<1)
		{
			S_Coordinate++;
		}else{
			S_Coordinate=0;
		}
		LCD12864_Display_Delay_Inspection_Refresh(&S_Delay_Inspection,&S_Coordinate);
		break;
	case K_2_num:	//
		if(S_Coordinate==0)
		{
			if(S_Delay_Inspection<5)
			{
				S_Delay_Inspection += 1;
				LCD12864_Display_Delay_Inspection_Refresh(&S_Delay_Inspection,&S_Coordinate);
			}
		}else if(S_Coordinate==1)
		{
			LCD12864_Display_Delay_Inspection_Refresh(&S_Delay_Inspection,&S_Coordinate);
			G_Delay_Inspection = S_Delay_Inspection;
			Init_Delay_Inspection(G_Delay_Inspection);
			LCD12864_Display_Success();	//��ʾ�ɹ�
			osDelay(1500);
			LCD12864_Display_Clear_Success();
		}
		break;
	case K_3_num:	//
		if(S_Coordinate==0)
		{
			if(S_Delay_Inspection>0)
			{
				S_Delay_Inspection -= 1;
				LCD12864_Display_Delay_Inspection_Refresh(&S_Delay_Inspection,&S_Coordinate);
			}
		}
		break;
	case K_4_num:	//
		if(Now_page == Delay_Inspection_page){
			printf("now_page == Delay_Inspection_page\r\n");
			//���ز˵�����
			LCD12864_Display(0x00,0x00);//����
			LCD12864_Display_Menu(NULL);
			S_Delay_Inspection = G_Delay_Inspection;
			Mark = 0;
			Now_page = Menu_Page;
			S_Coordinate=0;
			vTaskResume(Start_LCD12864_Menu_TaskHandle);//�ָ�����

			G_Delete_Task_struct.D_Task = Start_LCD12864_Delay_Inspection_TaskHandle;
			Start_LCD12864_Delay_Inspection_TaskHandle = NULL;
			G_Delete_Task_struct.sign = ENABLE;
		}
		break;
	default:
		break;
	}
}

void Start_LCD12864_Delay_Inspection_Task(void const * argument)
{
	BaseType_t err;
	uint32_t NotifyValue;
	LCD12864_Display(0x00,0x00);//����
	LCD12864_Display_Delay_Inspection_Page(NULL);//��һ�ν�����ʾȫ���˵�����
	while(1)
	{
		err = xTaskNotifyWait((uint32_t)0x00,	//2 �ȴ�������Ϣ
				(uint32_t)0xffffffff,
				(uint32_t*)&NotifyValue,
				(TickType_t)portMAX_DELAY);
		if(err==pdTRUE)
		{
			LCD12864_Display_Delay_Inspection_Page((uint8_t)NotifyValue);
		}
	}
}

