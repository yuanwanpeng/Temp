/*
 * LCD12864_Display_Menu.c
 *
 *  Created on: 2018��9��13��
 *      Author: YuanWP
 */
#include "LCD12864_Display_Menu.h"
#include "button.h"
#include "HUMI.h"
#include "relay.h"
#include "string.h"
#include "LCD12864.h"
#include "LCD12864_Display_Menu_Set_Strategy.h"
#include "LCD12864_Display_Menu_Route_Reset.h"
#include "LCD12864_Display_Menu_Stroking_Cycle.h"
#include "LCD12864_Display_Menu_Set_Strategy_Info.h"

/*
 * ���ѡ�������г̹�����������г̹����ĸ��ָĳɰ׵�
 * */
void LCD12864_Display_Menu_Typebase_opt(uint8_t opt,option* p_this_line)
{
	uint8_t* p_temp = Chinese_Menu_Type;
	uint8_t row,col,i,place,row_place = 0xB0;
	p_temp = p_temp + ((*p_this_line)*4*32);
	for(place = 0;place < 4;place++)		//���ٸ���
	{
		for(row = row_place+1;row >= row_place;row--)	//��8����Ϊһ���� һ�����ö�������ʾ
		WriteCommand(0x17-place);		//Set column address (MSB)//���еĿ�ʼ��ַ
		WriteCommand(0x00);				//Set column address (LSB)
		for(i = 0;i < 2;i++)			//(64/8)
		{
			for(col=0;col<8;col++)
			{
				if(opt == BLACK_BASE)	//�ڵ�
				{
					Write_Data(~(*p_temp++));
				}else if(opt == WHITE_BASE)	//�׵�
				{
					Write_Data(*p_temp++);
				}
			}
		}
	}
	printf("�г̹������ ���г̲�����ذ׵� !!!\r\n");
}

/*
 * ���ܼ�����
 */
void Dispose_Function_Key(option* p_this_line,Item_Menu* p_now_opt_select)
{
	switch(*p_this_line)
	{
	case Set_Strategy:		//��������
		if(Start_LCD12864_Set_Strategy_TaskHandle == NULL)
		{
		  osThreadDef(LCD12864_Set_Strategy_Task, Start_LCD12864_Set_Strategy_Task, osPriorityNormal, 0, 128);//�������Բ˵�ģ��
		  Start_LCD12864_Set_Strategy_TaskHandle = osThreadCreate(osThread(LCD12864_Set_Strategy_Task), NULL);
		  Now_page = Strategy_Menu;
		  vTaskSuspend( Start_LCD12864_Menu_TaskHandle );		//����lcd12864��ʾ���˵��Ľ���
		}
		break;
	case Route_Reset:		//�г̹���
		if(Start_LCD12864_Route_Reset_TaskHandle == NULL)
		{
		  osThreadDef(LCD12864_Route_Reset_Task, Start_LCD12864_Route_Reset_Task, osPriorityNormal, 0, 128);//�����г̹���
		  Start_LCD12864_Route_Reset_TaskHandle = osThreadCreate(osThread(LCD12864_Route_Reset_Task), NULL);
		  Now_page = Route_Reset_page;
		  vTaskSuspend( Start_LCD12864_Menu_TaskHandle );		//����lcd12864��ʾ���˵��Ľ���
		}
		break;
	case Max_Route:
		if(Start_LCD12864_Max_Route_TaskHandle == NULL)
		{
		  osThreadDef(LCD12864_Max_Route_Task, Start_LCD12864_Max_Route_Task, osPriorityNormal, 0, 128);//��������г�
		  Start_LCD12864_Max_Route_TaskHandle = osThreadCreate(osThread(LCD12864_Max_Route_Task), NULL);
		  Now_page = Max_Route_page;
		  vTaskSuspend( Start_LCD12864_Menu_TaskHandle );		//����lcd12864��ʾ���˵��Ľ���
		}
		break;
	case HUMI_Compensation:
		if(Start_LCD12864_HUMI_Compensation_TaskHandle == NULL)
		{
		  osThreadDef(LCD12864_HUMI_Compensation_Task, Start_LCD12864_HUMI_Compensation_Task, osPriorityNormal, 0, 128);//��������г�
		  Start_LCD12864_HUMI_Compensation_TaskHandle = osThreadCreate(osThread(LCD12864_HUMI_Compensation_Task), NULL);
		  Now_page = HUMI_Compensation_page;
		  vTaskSuspend( Start_LCD12864_Menu_TaskHandle );		//����lcd12864��ʾ���˵��Ľ���
		}
		break;
	case Delay_inspection:
		if(Start_LCD12864_Delay_Inspection_TaskHandle == NULL)
		{
		  osThreadDef(LCD12864_Delay_Inspection_Task, Start_LCD12864_Delay_Inspection_Task, osPriorityNormal, 0, 128);//��������г�
		  Start_LCD12864_Delay_Inspection_TaskHandle = osThreadCreate(osThread(LCD12864_Delay_Inspection_Task), NULL);
		  Now_page = Delay_Inspection_page;
		  vTaskSuspend( Start_LCD12864_Menu_TaskHandle );		//����lcd12864��ʾ���˵��Ľ���
		}
		break;
	case Set_Time:
		if(Start_LCD12864_Set_Time_TaskHandle == NULL)
		{
		  osThreadDef(LCD12864_Set_Time_Task, Start_LCD12864_Set_Time_Task, osPriorityNormal, 0, 128);//��������г�
		  Start_LCD12864_Set_Time_TaskHandle = osThreadCreate(osThread(LCD12864_Set_Time_Task), NULL);
		  Now_page = Set_Time_page;
		  vTaskSuspend( Start_LCD12864_Menu_TaskHandle );		//����lcd12864��ʾ���˵��Ľ���
		}
		break;
	case Stroking_Cycle:
		if(Start_LCD12864_Stroking_Cycle_TaskHandle == NULL)
		{
		  osThreadDef(LCD12864_Stroking_Cycle_Task, Start_LCD12864_Stroking_Cycle_Task, osPriorityNormal, 0, 128);
		  Start_LCD12864_Stroking_Cycle_TaskHandle = osThreadCreate(osThread(LCD12864_Stroking_Cycle_Task), NULL);
		  Now_page = Stroking_Cycle_page;
		  vTaskSuspend( Start_LCD12864_Menu_TaskHandle );		//����lcd12864��ʾ���˵��Ľ���
		}
		break;
	case Version_Information:
		break;
	}
}

/*
 * Ŀ����ʾȫ����ѡ��˵�
 * */
void LCD12864_Key_Null_Opt(option* p_this_line,uint8_t* p_page,Item_Menu* p_now_opt_select)
{
	if(*p_this_line < Delay_inspection)
	{
		LCD12864_Display_Set_Strategy(p_this_line);		//�������ÿ�
		LCD12864_Display_Route_Reset(p_this_line);			//
		LCD12864_Display_Max_Route(p_this_line);			//
		LCD12864_Display_HUMI_Compensation(p_this_line);
	}else{
		LCD12864_Display_Delay_inspection(p_this_line);
		LCD12864_Display_Set_Time(p_this_line);
		LCD12864_Display_Stroking_Cycle(p_this_line);
		LCD12864_Display_Version_Information(p_this_line);
	}
}

void LCD12864_Display_Menu_Option_Refresh(option* p_this_line,uint8_t opt)
{
//	Set_Strategy = 0,	//��������
//	Route_Reset,		//�г̹���
//	Max_Route,			//����г�
//	HUMI_Compensation,	//�¶Ȳ���
//	Delay_inspection,	//��ʱ���
//	Set_Time,			//ʱ��У׼
//	Stroking_Cycle,		//�г�����
//	Version_Information,//�汾��Ϣ
	switch(*p_this_line){
	case Set_Strategy:	//��ǰ�ڲ������ò��ܼ���
		if(opt==ADD_LINE)
		{
			(*p_this_line)++;
			LCD12864_Display_Set_Strategy(p_this_line);
			LCD12864_Display_Route_Reset(p_this_line);
		}
		break;
	case Route_Reset:
		if(opt==ADD_LINE)
		{
			(*p_this_line)++;
			LCD12864_Display_Route_Reset(p_this_line);
			LCD12864_Display_Max_Route(p_this_line);
		}else if(opt==SUB_LINE){
			(*p_this_line)--;
			LCD12864_Display_Set_Strategy(p_this_line);
			LCD12864_Display_Route_Reset(p_this_line);
		}
		break;
	case Max_Route:
		if(opt==ADD_LINE)
		{
			(*p_this_line)++;
			LCD12864_Display_Max_Route(p_this_line);
			LCD12864_Display_HUMI_Compensation(p_this_line);
		}else if(opt==SUB_LINE){
			(*p_this_line)--;
			LCD12864_Display_Route_Reset(p_this_line);
			LCD12864_Display_Max_Route(p_this_line);
		}
		break;
	case HUMI_Compensation:
		if(opt==ADD_LINE)
		{//ҳ����Ҫ��ת ��һҳ
//			(*p_this_line)++;
//			LCD12864_Display_Max_Route(p_this_line);
//			LCD12864_Display_HUMI_Compensation(p_this_line);
			(*p_this_line)++;
			LCD12864_Display_Delay_inspection(p_this_line);
			LCD12864_Display_Set_Time(p_this_line);
			LCD12864_Display_Stroking_Cycle(p_this_line);
			LCD12864_Display_Version_Information(p_this_line);

		}else if(opt==SUB_LINE){
			(*p_this_line)--;
			LCD12864_Display_Max_Route(p_this_line);
			LCD12864_Display_HUMI_Compensation(p_this_line);
		}
		break;
	case Delay_inspection:
		if(opt==ADD_LINE)
		{
			(*p_this_line)++;
			LCD12864_Display_Delay_inspection(p_this_line);
			LCD12864_Display_Set_Time(p_this_line);
		}else if(opt==SUB_LINE){//ҳ����Ҫ��ת ��һҳ
			(*p_this_line)--;
			LCD12864_Display_Set_Strategy(p_this_line);		//�������ÿ�
			LCD12864_Display_Route_Reset(p_this_line);			//
			LCD12864_Display_Max_Route(p_this_line);			//
			LCD12864_Display_HUMI_Compensation(p_this_line);
		}
		break;
	case Set_Time:
		if(opt==ADD_LINE)
		{
			(*p_this_line)++;
			LCD12864_Display_Set_Time(p_this_line);
			LCD12864_Display_Stroking_Cycle(p_this_line);
		}else if(opt==SUB_LINE){
			(*p_this_line)--;
			LCD12864_Display_Set_Time(p_this_line);
			LCD12864_Display_Delay_inspection(p_this_line);
		}
		break;
	case Stroking_Cycle:
		if(opt==ADD_LINE)
		{
			(*p_this_line)++;
			LCD12864_Display_Stroking_Cycle(p_this_line);
			LCD12864_Display_Version_Information(p_this_line);
		}else if(opt==SUB_LINE){
			(*p_this_line)--;
			LCD12864_Display_Stroking_Cycle(p_this_line);
			LCD12864_Display_Set_Time(p_this_line);
		}
		break;
	case Version_Information:
		if(opt==ADD_LINE)
		{
		}else if(opt==SUB_LINE){
			(*p_this_line)--;
			LCD12864_Display_Version_Information(p_this_line);
			LCD12864_Display_Stroking_Cycle(p_this_line);
		}
		break;

	}
}

void LCD12864_Display_Menu(uint8_t key)
{
//	osThreadId Old_Start_LCD12864_Menu_TaskHandle;
	static option this_line = Set_Strategy;
	static uint8_t page = 0;
	static Item_Menu now_opt_select = At_Null;
	switch(key)
	{
	case NULL:	//��һ�ν�����ʾȫ���˵�����
		LCD12864_Key_Null_Opt(&this_line,&page,&now_opt_select);
		break;
	case K_1_num://ѡ�񰴼�
		Dispose_Function_Key(&this_line,&now_opt_select);
		break;
	case K_2_num:	//���� this_line   this_line =��ǰ�Ѿ��������
		if(this_line>Set_Strategy)//�ڶ����жϱ�ʾ��ǰ�����°�����Ч�����Ĳ˵�ѡ����
		{
			LCD12864_Display_Menu_Option_Refresh(&this_line,SUB_LINE);//��һ��
		}
		break;
	case K_3_num:	//���� this_line+1   this_line =��ǰ�Ѿ��������
		if(this_line<Version_Information)//�ڶ����жϱ�ʾ��ǰ�����°�����Ч�����Ĳ˵�ѡ����
		{
			LCD12864_Display_Menu_Option_Refresh(&this_line,ADD_LINE);//��һ��
		}
		break;
	case K_4_num:	//���� this_line+1   this_line =��ǰ�Ѿ��������
		if(now_opt_select == At_Null)//��ʾ�����˵��£����·��ذ�����ʾҪ�ص���ʾ�����¶Ƚ��� (��ԭ������)
		{
			this_line = Set_Strategy;
			page = 0;
			LCD12864_Display(0x00,0x00);
			LCD12864_Put_Str_At_Present_Mode(G_New_Mode);
			LCD12864_Put_Signel_Sim();
			LCD12864_Put_Signel_Wifi();
			LCD12864_Put_Motor_Situation(1);
			LCD12864_Put_Open_Mouth_And_Time();
			vTaskResume(Start_LCD12864_HUMI_TaskHandle);//�ָ�lcd12864��ʾ�¶ȵĽ���
			//��Ҫ����
			G_Delete_Task_struct.sign = ENABLE;
			G_Delete_Task_struct.D_Task = Start_LCD12864_Menu_TaskHandle;
			Start_LCD12864_Menu_TaskHandle = NULL;
		}
		break;
	default:

		break;
	}
}


/*
 * ��ʾ�˵�����
 * 	�г̹���  ��λ
 * 	����г�  ___
 * 	�¶Ȳ���  ___
 * 	��ʱ���  ___
 */
void Start_LCD12864_Display_Menu_Task(void const * argument)
{
	BaseType_t err;
	uint32_t NotifyValue;
	LCD12864_Display(0x00,0x00);//����
	LCD12864_Display_Menu(NULL);//��һ�ν�����ʾȫ���˵�����
	Now_page = Menu_Page;
	while(1)
	{
		err = xTaskNotifyWait((uint32_t)0x00,			//2 �ȴ�������Ϣ
							(uint32_t)0xffffffff,
							(uint32_t*)&NotifyValue,
							(TickType_t)portMAX_DELAY);
		Now_page = Menu_Page;

		if(err==pdTRUE)
		{
			LCD12864_Display_Menu((uint8_t)NotifyValue);
		}
	}
}


/*
 * 1.��������
 */
void LCD12864_Display_Set_Strategy(option* this_line)
{
	uint8_t color;
	if(*this_line == Set_Strategy){
		color = BLACK_BASE;
	}else{
		color = WHITE_BASE;
	}
	LCD12864_Put_8_16_Char(0xB7,0x04,'1',color);
	LCD12864_Put_8_16_Char(0xB7,0x0C,'.',color);
	LCD12864_Put_16_16_Char(0xB7,0x14,0x00,color);//����
	LCD12864_Put_16_16_Char(0xB7,0x24,0x01,color);//����
	LCD12864_Put_16_16_Char(0xB7,0x34,0x02,color);//����
	LCD12864_Put_16_16_Char(0xB7,0x44,0x03,color);//����
}
/*
 * 2.�г̹���
 */
void LCD12864_Display_Route_Reset(option* this_line)
{
	uint8_t color;
	if(*this_line == Route_Reset){
		color = BLACK_BASE;
	}else{
		color = WHITE_BASE;
	}
	LCD12864_Put_8_16_Char(0xB5,0x04,'2',color);
	LCD12864_Put_8_16_Char(0xB5,0x0C,'.',color);
	LCD12864_Put_16_16_Char(0xB5,0x14,0x04,color);//����
	LCD12864_Put_16_16_Char(0xB5,0x24,0x05,color);//����
	LCD12864_Put_16_16_Char(0xB5,0x34,0x06,color);//����
	LCD12864_Put_16_16_Char(0xB5,0x44,0x07,color);//����
}
/*
 * 3.����г�
 */
void LCD12864_Display_Max_Route(option* this_line)
{
	uint8_t color;
	if(*this_line == Max_Route){
		color = BLACK_BASE;
	}else{
		color = WHITE_BASE;
	}
	LCD12864_Put_8_16_Char(0xB3,0x04,'3',color);
	LCD12864_Put_8_16_Char(0xB3,0x0C,'.',color);
	LCD12864_Put_16_16_Char(0xB3,0x14,0x08,color);//����
	LCD12864_Put_16_16_Char(0xB3,0x24,0x09,color);//����
	LCD12864_Put_16_16_Char(0xB3,0x34,0x04,color);//����
	LCD12864_Put_16_16_Char(0xB3,0x44,0x05,color);//����
}
/*
 * 4.�¶Ȳ���
 */
void LCD12864_Display_HUMI_Compensation(option* this_line)
{
	uint8_t color;
	if(*this_line == HUMI_Compensation){
		color = BLACK_BASE;
	}else{
		color = WHITE_BASE;
	}
	LCD12864_Put_8_16_Char(0xB1,0x04,'4',color);
	LCD12864_Put_8_16_Char(0xB1,0x0C,'.',color);
	LCD12864_Put_16_16_Char(0xB1,0x14,0x0A,color);//����
	LCD12864_Put_16_16_Char(0xB1,0x24,0x0B,color);//����
	LCD12864_Put_16_16_Char(0xB1,0x34,0x0C,color);//����
	LCD12864_Put_16_16_Char(0xB1,0x44,0x0D,color);//����
}
/*
 * 5.��ʱ���
 */
void LCD12864_Display_Delay_inspection(option* this_line)
{
	uint8_t color;
	if(*this_line == Delay_inspection){
		color = BLACK_BASE;
	}else{
		color = WHITE_BASE;
	}
	LCD12864_Put_8_16_Char(0xB7,0x04,'5',color);
	LCD12864_Put_8_16_Char(0xB7,0x0C,'.',color);
	LCD12864_Put_16_16_Char(0xB7,0x14,0x0E,color);//����
	LCD12864_Put_16_16_Char(0xB7,0x24,0x0F,color);//ʱ��
	LCD12864_Put_16_16_Char(0xB7,0x34,0x10,color);//����
	LCD12864_Put_16_16_Char(0xB7,0x44,0x11,color);//����
}
/*
 * 6.ʱ��У׼
 */
void LCD12864_Display_Set_Time(option* this_line)
{
	uint8_t color;
	if(*this_line == Set_Time){
		color = BLACK_BASE;
	}else{
		color = WHITE_BASE;
	}
	LCD12864_Put_8_16_Char(0xB5,0x04,'6',color);
	LCD12864_Put_8_16_Char(0xB5,0x0C,'.',color);
	LCD12864_Put_16_16_Char(0xB5,0x14,0x0F,color);//ʱ��
	LCD12864_Put_16_16_Char(0xB5,0x24,0x12,color);//����
	LCD12864_Put_16_16_Char(0xB5,0x34,0x13,color);//У��
	LCD12864_Put_16_16_Char(0xB5,0x44,0x14,color);//׼��
}
/*
 * 7.�г�����
 */
void LCD12864_Display_Stroking_Cycle(option* this_line)
{
	uint8_t color;
	if(*this_line == Stroking_Cycle){
		color = BLACK_BASE;
	}else{
		color = WHITE_BASE;
	}
	LCD12864_Put_8_16_Char(0xB3,0x04,'7',color);
	LCD12864_Put_8_16_Char(0xB3,0x0C,'.',color);
	LCD12864_Put_16_16_Char(0xB3,0x14,0x04,color);//����
	LCD12864_Put_16_16_Char(0xB3,0x24,0x05,color);//����
	LCD12864_Put_16_16_Char(0xB3,0x34,0x15,color);//����
	LCD12864_Put_16_16_Char(0xB3,0x44,0x16,color);//����
}
/*
 * 8.�汾��Ϣ
 */
void LCD12864_Display_Version_Information(option* this_line)
{
	uint8_t color;
	if(*this_line == Version_Information){
		color = BLACK_BASE;
	}else{
		color = WHITE_BASE;
	}
	LCD12864_Put_8_16_Char(0xB1,0x04,'8',color);
	LCD12864_Put_8_16_Char(0xB1,0x0C,'.',color);
	LCD12864_Put_16_16_Char(0xB1,0x14,0x17,color);//����
	LCD12864_Put_16_16_Char(0xB1,0x24,0x18,color);//����
	LCD12864_Put_16_16_Char(0xB1,0x34,0x19,color);//����
	LCD12864_Put_16_16_Char(0xB1,0x44,0x1A,color);//Ϣ��
}







