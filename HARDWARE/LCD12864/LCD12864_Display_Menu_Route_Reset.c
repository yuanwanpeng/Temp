/*
 * LCD12864_Display_Menu_Route_Reset.c
 *
 *  Created on: 2018��10��18��
 *      Author: YuanWP
 */
#include "LCD12864_Display_Menu_Route_Reset.h"
#include "button.h"
#include "HUMI.h"
#include "relay.h"
#include "string.h"
#include "LCD12864.h"
#include "LCD12864_Display_Menu_Set_Strategy.h"

osThreadId Start_LCD12864_Route_Reset_TaskHandle = NULL;

void LCD12864_Display_Now_Route(void)
{
	LCD12864_Put_16_16_Char(0xB7,0x14,0x26,WHITE_BASE);//����
	LCD12864_Put_16_16_Char(0xB7,0x24,0x27,WHITE_BASE);//ǰ��
	LCD12864_Put_16_16_Char(0xB7,0x34,0x04,WHITE_BASE);//����
	LCD12864_Put_16_16_Char(0xB7,0x44,0x05,WHITE_BASE);//����
	LCD12864_Put_8_16_Char(0xB7,0x54,':',WHITE_BASE);

	LCD12864_Display_Now_Route_Refresh();

	LCD12864_Put_16_16_Char(0xB5,0x54,0x2E,WHITE_BASE);//����

	LCD12864_Put_16_16_Char(0xB3,0x14,0x1B,BLACK_BASE);//����
	LCD12864_Put_16_16_Char(0xB3,0x24,0x1C,BLACK_BASE);//λ��
}
/*
 * ˢ�µ�ǰ�г̵�����
 */
void LCD12864_Display_Now_Route_Refresh(void)
{
	char Route[10];
	memset(Route,'0',sizeof(Route));

	sprintf(Route,"%04d",(int8_t)G_Now_Route);

	LCD12864_Put_8_16_Char(0xB5,0x2a,Route[0],WHITE_BASE);
	LCD12864_Put_8_16_Char(0xB5,0x32,Route[1],WHITE_BASE);
	LCD12864_Put_8_16_Char(0xB5,0x3a,Route[2],WHITE_BASE);
	LCD12864_Put_8_16_Char(0xB5,0x42,Route[3],WHITE_BASE);
}
/*
 * ��ӡ�˽���
 * */
void LCD12864_Route_Reset_Key_Null_Opt(void)
{
	LCD12864_Display_Now_Route();		//��ǰ�г�
//	LCD12864_Display_Route_Reset();		//
}
/*
 * �г̸�λ����
 */
void LCD12864_Display_Route_Reset_Page(uint8_t key)
{
	switch(key)
	{
	case NULL:	//��һ�ν�����ʾȫ���˵�����
		LCD12864_Route_Reset_Key_Null_Opt();
		break;
	case K_1_num://ѡ�񰴼�
//		G_Route_Reset();
//		LCD12864_Display_Now_Route_Refresh();
		//��λ�г�
		break;
	case K_2_num:	//���ϰ������ڴ�Ϊ ȷ��
		G_Route_Reset();
		LCD12864_Display_Now_Route_Refresh();
		LCD12864_Display_Success();	//��ʾ�ɹ�
		osDelay(1500);
		LCD12864_Display_Clear_Success();
		break;
	case K_3_num:	//
		break;
	case K_4_num:	//
		if(Now_page == Route_Reset_page){
			printf("now_page == Route_Reset_page\r\n");
			//���ز˵�����
			LCD12864_Display(0x00,0x00);//����
			LCD12864_Display_Menu(NULL);
			Now_page = Menu_Page;
			vTaskResume(Start_LCD12864_Menu_TaskHandle);//�ָ�����
			G_Delete_Task_struct.D_Task = Start_LCD12864_Route_Reset_TaskHandle;
			Start_LCD12864_Route_Reset_TaskHandle = NULL;
			G_Delete_Task_struct.sign = ENABLE;
		}

		break;
	default:
		break;
	}
}
/*
 * �г̸�λ����
 * */
void Start_LCD12864_Route_Reset_Task(void const * argument)
{
	BaseType_t err;
	uint32_t NotifyValue;
	LCD12864_Display(0x00,0x00);//����
	LCD12864_Display_Route_Reset_Page(NULL);//��һ�ν�����ʾȫ���˵�����
	while(1)
	{
		err = xTaskNotifyWait((uint32_t)0x00,			//2 �ȴ�������Ϣ
				(uint32_t)0xffffffff,
				(uint32_t*)&NotifyValue,
				(TickType_t)portMAX_DELAY);
		if(err==pdTRUE)
		{
			LCD12864_Display_Route_Reset_Page((uint8_t)NotifyValue);
		}
	}
}






