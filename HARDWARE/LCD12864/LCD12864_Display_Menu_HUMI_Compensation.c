/*
 * LCD12864_Display_Menu_HUMI_Compensation.c
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
#include "LCD12864_Display_Menu_HUMI_Compensation.h"

osThreadId Start_LCD12864_HUMI_Compensation_TaskHandle;

void LCD12864_Display_HUMI_Compensation_Interior(int8_t* p_S_comp,uint8_t* p_Coordinate)
{
	LCD12864_Put_16_16_Char(0xB7,0x14,0x0A,WHITE_BASE);//����
	LCD12864_Put_16_16_Char(0xB7,0x24,0x0B,WHITE_BASE);//����
	LCD12864_Put_16_16_Char(0xB7,0x34,0x0C,WHITE_BASE);//����
	LCD12864_Put_16_16_Char(0xB7,0x44,0x0D,WHITE_BASE);//����
	LCD12864_Put_8_16_Char(0xB7,0x54,':',WHITE_BASE);

	LCD12864_Display_HUMI_Compensation_Refresh(p_S_comp,p_Coordinate);

	LCD12864_Put_16_16_Char(0xB5,0x54,0x2F,WHITE_BASE);//����

	LCD12864_Put_16_16_Char(0xB3,0x14,0x02,WHITE_BASE);//����
	LCD12864_Put_16_16_Char(0xB3,0x24,0x03,WHITE_BASE);//����

}
void LCD12864_Display_HUMI_Compensation_Refresh(int8_t* p_S_comp,uint8_t* p_Coordinate)
{
	char comp_arr[5];
	memset(comp_arr,'0',sizeof(comp_arr));

	if(*p_S_comp>=0)
	{
		sprintf(comp_arr,"%02d",*p_S_comp);
		LCD12864_Put_8_16_Char(0xB5,0x2a,comp_arr[0],(*p_Coordinate)==0);
		LCD12864_Put_8_16_Char(0xB5,0x32,'.',(*p_Coordinate)==0);
		LCD12864_Put_8_16_Char(0xB5,0x3a,comp_arr[1],(*p_Coordinate)==0);
		LCD12864_Put_8_16_Char(0xB5,0x42,' ',WHITE_BASE);
	}else{
		sprintf(comp_arr,"%03d",*p_S_comp);
		LCD12864_Put_8_16_Char(0xB5,0x2a,comp_arr[0],(*p_Coordinate)==0);
		LCD12864_Put_8_16_Char(0xB5,0x32,comp_arr[1],(*p_Coordinate)==0);
		LCD12864_Put_8_16_Char(0xB5,0x3a,'.',(*p_Coordinate)==0);
		LCD12864_Put_8_16_Char(0xB5,0x42,comp_arr[2],(*p_Coordinate)==0);
	}

	LCD12864_Put_16_16_Char(0xB3,0x14,0x02,(*p_Coordinate)==1);//����
	LCD12864_Put_16_16_Char(0xB3,0x24,0x03,(*p_Coordinate)==1);//����
}
/*
 * ��ӡ�˽���
 * */
void LCD12864_HUMI_Compensation_Key_Null_Opt(int8_t* p_S_comp,uint8_t* p_Coordinate)
{
	LCD12864_Display_HUMI_Compensation_Interior(p_S_comp,p_Coordinate);		//��ǰ�г�
}
void LCD12864_Display_HUMI_Compensation_Page(uint8_t key)
{
	static int8_t S_comp = 0;
	static uint8_t Mark = 0;
	static uint8_t S_Coordinate = 0;//��ǰ����
	if(Mark==0)
	{
		S_comp = (int8_t)(comp*10);
		Mark = 1;
	}
	switch(key)
	{
	case NULL:	//��һ�ν�����ʾȫ���˵�����
		LCD12864_HUMI_Compensation_Key_Null_Opt(&S_comp,&S_Coordinate);
		break;
	case K_1_num://ѡ�񰴼�
//		LCD12864_Display_HUMI_Compensation_Refresh(&S_comp);
//		comp = ((float)S_comp)/10;
//		AT24CXX_Write(HUMI_COMP,(uint8_t*)&S_comp,sizeof(S_comp));
		//�л�����һѡ��
		if(S_Coordinate<1)
		{
			S_Coordinate++;
		}else{
			S_Coordinate=0;
		}
		LCD12864_Display_HUMI_Compensation_Refresh(&S_comp,&S_Coordinate);
		break;
	case K_2_num:	//
		if(S_Coordinate==0)//��������������
		{
			if(S_comp<50)
			{
				S_comp += 1;
				LCD12864_Display_HUMI_Compensation_Refresh(&S_comp,&S_Coordinate);
			}
		}else if(S_Coordinate==1)
		{
			LCD12864_Display_HUMI_Compensation_Refresh(&S_comp,&S_Coordinate);
			comp = ((float)S_comp)/10;
			AT24CXX_Write(HUMI_COMP,(uint8_t*)&S_comp,sizeof(S_comp));
			LCD12864_Display_Success();	//��ʾ�ɹ�
			osDelay(1500);
			LCD12864_Display_Clear_Success();
		}
		break;
	case K_3_num:	//
		if(S_Coordinate==0)//��������������
		{
			if(S_comp>(-50))
			{
				S_comp -= 1;
				LCD12864_Display_HUMI_Compensation_Refresh(&S_comp,&S_Coordinate);
			}
		}
		break;
	case K_4_num:	//
		if(Now_page == HUMI_Compensation_page){
			printf("now_page == HUMI_Compensation_page\r\n");
			//���ز˵�����
			LCD12864_Display(0x00,0x00);//����
			LCD12864_Display_Menu(NULL);
			S_comp = (int8_t)(comp*10);
			Mark = 0;
			Now_page = Menu_Page;
			S_Coordinate = 0;
			vTaskResume(Start_LCD12864_Menu_TaskHandle);//�ָ�����

			G_Delete_Task_struct.D_Task = Start_LCD12864_HUMI_Compensation_TaskHandle;
			Start_LCD12864_HUMI_Compensation_TaskHandle = NULL;
			G_Delete_Task_struct.sign = ENABLE;
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
	LCD12864_Display(0x00,0x00);//����
	LCD12864_Display_HUMI_Compensation_Page(NULL);//��һ�ν�����ʾȫ���˵�����
	while(1)
	{
		err = xTaskNotifyWait((uint32_t)0x00,	//2 �ȴ�������Ϣ
				(uint32_t)0xffffffff,
				(uint32_t*)&NotifyValue,
				(TickType_t)portMAX_DELAY);
		if(err==pdTRUE)
		{
			LCD12864_Display_HUMI_Compensation_Page((uint8_t)NotifyValue);
		}
	}
}
