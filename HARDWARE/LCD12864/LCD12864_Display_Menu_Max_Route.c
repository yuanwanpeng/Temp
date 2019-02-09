/*
 * LCD12864_Display_Menu_Max_Route.c
 *
 *  Created on: 2018��10��19��
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

osThreadId Start_LCD12864_Max_Route_TaskHandle = NULL;

void LCD12864_Display_Max_Route_Interior(uint16_t* p_S_Max_Route,uint8_t* p_Coordinate)
{
	LCD12864_Put_16_16_Char(0xB7,0x14,0x08,WHITE_BASE);//����
	LCD12864_Put_16_16_Char(0xB7,0x24,0x09,WHITE_BASE);//����
	LCD12864_Put_16_16_Char(0xB7,0x34,0x04,WHITE_BASE);//����
	LCD12864_Put_16_16_Char(0xB7,0x44,0x05,WHITE_BASE);//����
	LCD12864_Put_8_16_Char(0xB7,0x54,':',WHITE_BASE);

	LCD12864_Display_Max_Route_Refresh(p_S_Max_Route,p_Coordinate);

	LCD12864_Put_16_16_Char(0xB5,0x54,0x2E,WHITE_BASE);//����

	LCD12864_Put_16_16_Char(0xB3,0x14,0x02,WHITE_BASE);//����
	LCD12864_Put_16_16_Char(0xB3,0x24,0x03,WHITE_BASE);//����

}
void LCD12864_Display_Max_Route_Refresh(uint16_t* p_S_Max_Route,uint8_t* p_Coordinate)
{
	char Route[10];
	memset(Route,'0',sizeof(Route));

	sprintf(Route,"%04d",*p_S_Max_Route);

	LCD12864_Put_8_16_Char(0xB5,0x2a,Route[0],(*p_Coordinate)==0);
	LCD12864_Put_8_16_Char(0xB5,0x32,Route[1],(*p_Coordinate)==1);
	LCD12864_Put_8_16_Char(0xB5,0x3a,Route[2],(*p_Coordinate)==2);
	LCD12864_Put_8_16_Char(0xB5,0x42,Route[3],(*p_Coordinate)==3);
	if((*p_Coordinate)==4)
	{
		LCD12864_Put_16_16_Char(0xB3,0x14,0x02,BLACK_BASE);//����
		LCD12864_Put_16_16_Char(0xB3,0x24,0x03,BLACK_BASE);//����
	}else if((*p_Coordinate)==0)
	{
		LCD12864_Put_16_16_Char(0xB3,0x14,0x02,WHITE_BASE);//����
		LCD12864_Put_16_16_Char(0xB3,0x24,0x03,WHITE_BASE);//����
	}
}
/*
 * ��ӡ�˽���
 * */
void LCD12864_Max_Route_Key_Null_Opt(uint16_t* p_S_Max_Route,uint8_t* p_Coordinate)
{
	LCD12864_Display_Max_Route_Interior(p_S_Max_Route,p_Coordinate);		//��ǰ�г�
}
/*
 * ��һλ
 * */
void LCD12864_Display_Max_Route_Add(uint16_t* p_S_Max_Route,uint8_t* p_Coordinate)
{
	switch(*p_Coordinate){
	case 0:
		if(((*p_S_Max_Route)/1000)<9)
		{
			(*p_S_Max_Route) += 1000;
		}
		LCD12864_Display_Max_Route_Refresh(p_S_Max_Route,p_Coordinate);
		break;
	case 1:
		if(((*p_S_Max_Route)%1000/100)<9)
		{
			(*p_S_Max_Route) += 100;
		}
		LCD12864_Display_Max_Route_Refresh(p_S_Max_Route,p_Coordinate);
		break;
	case 2:
		if(((*p_S_Max_Route)%100/10)<9)
		{
			(*p_S_Max_Route) += 10;
		}
		LCD12864_Display_Max_Route_Refresh(p_S_Max_Route,p_Coordinate);
		break;
	case 3:
		if(((*p_S_Max_Route)%10)<9)
		{
			(*p_S_Max_Route) += 1;
		}
		LCD12864_Display_Max_Route_Refresh(p_S_Max_Route,p_Coordinate);
		break;
	}
}
/*
 * ��һλ
 * */
void LCD12864_Display_Max_Route_Sub(uint16_t* p_S_Max_Route,uint8_t* p_Coordinate)
{
	switch(*p_Coordinate){
	case 0:
		if(((*p_S_Max_Route)/1000)>0)
		{
			(*p_S_Max_Route) -= 1000;
		}
		LCD12864_Display_Max_Route_Refresh(p_S_Max_Route,p_Coordinate);
		break;
	case 1:
		if(((*p_S_Max_Route)%1000/100)>0)
		{
			(*p_S_Max_Route) -= 100;
		}
		LCD12864_Display_Max_Route_Refresh(p_S_Max_Route,p_Coordinate);
		break;
	case 2:
		if(((*p_S_Max_Route)%100/10)>0)
		{
			(*p_S_Max_Route) -= 10;
		}
		LCD12864_Display_Max_Route_Refresh(p_S_Max_Route,p_Coordinate);
		break;
	case 3:
		if(((*p_S_Max_Route)%10)>0)
		{
			(*p_S_Max_Route) -= 1;
		}
		LCD12864_Display_Max_Route_Refresh(p_S_Max_Route,p_Coordinate);
		break;
	}
}
void LCD12864_Display_Max_Route_Page(uint8_t key)
{
	static uint16_t S_Max_Route = 0;
	static uint8_t Mark = 0;
	static uint8_t S_Coordinate = 0;//��ǰ����
	if(Mark==0)
	{
		S_Max_Route = G_Max_Route;
		Mark = 1;
	}
	switch(key)
	{
	case NULL:	//��һ�ν�����ʾȫ���˵�����
		LCD12864_Max_Route_Key_Null_Opt(&S_Max_Route,&S_Coordinate);
		break;
	case K_1_num://ѡ�񰴼�
//		LCD12864_Display_Max_Route_Refresh(&S_Max_Route);
//		Init_Max_Route(S_Max_Route);	//��λ�г�
		//�л�����һѡ��
		if(S_Coordinate<4)
		{
			S_Coordinate++;
		}else{
			S_Coordinate=0;
		}
		LCD12864_Display_Max_Route_Refresh(&S_Max_Route,&S_Coordinate);
		break;
	case K_2_num:	//����
		if(S_Coordinate == 4){
			LCD12864_Display_Max_Route_Refresh(&S_Max_Route,&S_Coordinate);
			Init_Max_Route(S_Max_Route);		//��ʼ������г�
			LCD12864_Display_Success();			//��ʾ�ɹ�
			osDelay(1500);
			LCD12864_Display_Clear_Success();
		}
		LCD12864_Display_Max_Route_Add(&S_Max_Route,&S_Coordinate);
		break;
	case K_3_num:	//����
		LCD12864_Display_Max_Route_Sub(&S_Max_Route,&S_Coordinate);
		break;
	case K_4_num:	//
		if(Now_page == Max_Route_page){
			printf("now_page == Max_Route_page\r\n");
			//���ز˵�����
			LCD12864_Display(0x00,0x00);//����
			LCD12864_Display_Menu(NULL);
			S_Max_Route = G_Max_Route;
			Mark = 0;
			Now_page = Menu_Page;
			S_Coordinate = 0;
			vTaskResume(Start_LCD12864_Menu_TaskHandle);//�ָ�����
			G_Delete_Task_struct.D_Task = Start_LCD12864_Max_Route_TaskHandle;
			Start_LCD12864_Max_Route_TaskHandle = NULL;
			G_Delete_Task_struct.sign = ENABLE;
		}
		break;
	default:
		break;
	}
}

void Start_LCD12864_Max_Route_Task(void const * argument)
{
	BaseType_t err;
	uint32_t NotifyValue;
	LCD12864_Display(0x00,0x00);//����
	LCD12864_Display_Max_Route_Page(NULL);//��һ�ν�����ʾȫ���˵�����
	while(1)
	{
		err = xTaskNotifyWait((uint32_t)0x00,	//2 �ȴ�������Ϣ
				(uint32_t)0xffffffff,
				(uint32_t*)&NotifyValue,
				(TickType_t)portMAX_DELAY);
		if(err==pdTRUE)
		{
			LCD12864_Display_Max_Route_Page((uint8_t)NotifyValue);
		}
	}
}







