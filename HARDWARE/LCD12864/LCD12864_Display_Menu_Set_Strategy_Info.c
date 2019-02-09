/*
 * LCD12864_Display_Menu_Set_Strategy_Info.c
 *
 *  Created on: 2018��11��7��
 *      Author: YuanWP
 */
#include "LCD12864_Display_Menu_Set_Strategy_Info.h"
#include "LCD12864_Display_Menu_Set_Strategy.h"
#include "string.h"

Strategy_struct S_Strategy[8];		//8�����Ի�����
osThreadId Start_LCD12864_Set_Strategy_Info_TaskHandle;	//���Ĳ�����Ϣ���


void LCD12864_Set_Strategy_Info_Refresh(uint8_t* p_Place,Line_Num* p_Line_Num)
{
	LCD12864_Set_Strategy_Info_Line1(p_Place,p_Line_Num);//��ʾline1~line4
	LCD12864_Set_Strategy_Info_Line2(p_Place,p_Line_Num);
	LCD12864_Set_Strategy_Info_Line3(p_Place,p_Line_Num);
	LCD12864_Set_Strategy_Info_Line4(p_Place,p_Line_Num);
}
/*
 * ���ϰ��������ڲ�����Ϣ���ý���
 */
void LCD12864_Set_Strategy_Info_Up_Key_Opt(uint8_t* p_Place,Line_Num* p_Line_Num)
{
	switch(*p_Place){
	case STRATEGY_INFO_SWITCH:	//��ǰ��ѡ��
		if(S_Strategy[(*p_Line_Num)].Strategy_State == Strategy_Open)
		{
			S_Strategy[(*p_Line_Num)].Strategy_State = Strategy_Close;
		}else{
			S_Strategy[(*p_Line_Num)].Strategy_State = Strategy_Open;
		}
		break;
	case STRATEGY_INFO_STANDARD://��ǰ�ڷ�ڻ����¶�
		if(S_Strategy[(*p_Line_Num)].Strategy_Type == Strategy_Type_Route)
		{
			S_Strategy[(*p_Line_Num)].Strategy_Type = Strategy_Type_Temp;
		}else{
			S_Strategy[(*p_Line_Num)].Strategy_Type = Strategy_Type_Route;
		}
		break;
	case STRATEGY_INFO_TIME_HOURS://��ǰ��Сʱ
		if(S_Strategy[(*p_Line_Num)].Time.Hours < 23)
		{
			S_Strategy[(*p_Line_Num)].Time.Hours += 1;
		}
		break;
	case STRATEGY_INFO_TIME_MINUTES://��ǰ�ڷ���
		if(S_Strategy[(*p_Line_Num)].Time.Minutes < 59)
		{
			S_Strategy[(*p_Line_Num)].Time.Minutes += 1;
		}
		break;
	case STRATEGY_INFO_ROUTE_4://�г̵�ǧλ
		if((S_Strategy[(*p_Line_Num)].Route/1000) < 9)
		{
			S_Strategy[(*p_Line_Num)].Route += 1000;
		}
		break;
	case STRATEGY_INFO_ROUTE_3://�г̵İ�λ
		if((S_Strategy[(*p_Line_Num)].Route%1000/100) < 9)
		{
			S_Strategy[(*p_Line_Num)].Route += 100;
		}
		break;
	case STRATEGY_INFO_ROUTE_2://�г̵�ʮλ
		if((S_Strategy[(*p_Line_Num)].Route%100/10) < 9)
		{
			S_Strategy[(*p_Line_Num)].Route += 10;
		}
		break;
	case STRATEGY_INFO_ROUTE_1://�г̸�λ
		if((S_Strategy[(*p_Line_Num)].Route%10) < 9)
		{
			S_Strategy[(*p_Line_Num)].Route += 1;
		}
		break;
	case STRATEGY_INFO_MIN_TEMP://��С�¶�
		if((S_Strategy[(*p_Line_Num)].Temp_l) < 60)
		{
			S_Strategy[(*p_Line_Num)].Temp_l += 1;
			if((S_Strategy[(*p_Line_Num)].Temp_l+STRATEGY_INFO_TEMP_SECTION)>S_Strategy[(*p_Line_Num)].Temp_h)
			{//������� ���ڸ��µĻ�
				S_Strategy[(*p_Line_Num)].Temp_h = S_Strategy[(*p_Line_Num)].Temp_l+STRATEGY_INFO_TEMP_SECTION;
			}
		}
		break;
	case STRATEGY_INFO_MAX_TEMP://���
		if((S_Strategy[(*p_Line_Num)].Temp_h) < 63)
		{
			S_Strategy[(*p_Line_Num)].Temp_h += 1;
		}
		break;
	case STRATEGY_INFO_SET://����ȷ��
		//д��G_Strategy
		if(S_Strategy[(*p_Line_Num)].Strategy_State == Strategy_Close)//����ر��˵�ǰ��
		{
			Init_Strategy((*p_Line_Num));//�ӵ�ǰ���Ժ��д��
		}

		if(S_Strategy[(*p_Line_Num)].Strategy_Type == Strategy_Type_Route)
		{
			if(S_Strategy[(*p_Line_Num)].Route > G_Now_Route)//����ȫ�ֵ�����г�
			{
				S_Strategy[(*p_Line_Num)].Route = G_Max_Route;//���ó�����г�
			}
		}

		memcpy((uint8_t*)G_Strategy,(uint8_t*)S_Strategy,sizeof(S_Strategy));//���

		AT24CXX_Write((*p_Line_Num)*0x10,((uint8_t*)S_Strategy)+(sizeof(S_Strategy[(*p_Line_Num)])*(*p_Line_Num)),sizeof(S_Strategy[(*p_Line_Num)]));
		LCD12864_Display_Success();	//��ʾ�ɹ�
		osDelay(1500);
		LCD12864_Display_Clear_Success();
		break; 
	}
}
/*
 * ���°��������ڲ�����Ϣ���ý���
 * ע��ͬ��
 */
void LCD12864_Set_Strategy_Info_Down_Key_Opt(uint8_t* p_Place,Line_Num* p_Line_Num)
{
	uint16_t Min_Time,UP_Min_Time;

	switch(*p_Place){
	case STRATEGY_INFO_SWITCH:
		if(S_Strategy[(*p_Line_Num)].Strategy_State == Strategy_Open)
		{
			S_Strategy[(*p_Line_Num)].Strategy_State = Strategy_Close;
		}else{
			S_Strategy[(*p_Line_Num)].Strategy_State = Strategy_Open;
		}
		break;
	case STRATEGY_INFO_STANDARD:
		if(S_Strategy[(*p_Line_Num)].Strategy_Type == Strategy_Type_Route)
		{
			S_Strategy[(*p_Line_Num)].Strategy_Type = Strategy_Type_Temp;
		}else{
			S_Strategy[(*p_Line_Num)].Strategy_Type = Strategy_Type_Route;
		}
		break;
	case STRATEGY_INFO_TIME_HOURS:
		if((*p_Line_Num) == 0)
		{
			if(S_Strategy[(*p_Line_Num)].Time.Hours > 4)
			{
				S_Strategy[(*p_Line_Num)].Time.Hours -= 1;
			}
		}else{
			Min_Time = (S_Strategy[(*p_Line_Num)].Time.Hours-1) * 60 + S_Strategy[(*p_Line_Num)].Time.Minutes;//�������ǰ��������ʱ��
			UP_Min_Time = (S_Strategy[((*p_Line_Num)-1)].Time.Hours) * 60 + S_Strategy[((*p_Line_Num)-1)].Time.Minutes;//��һ����������ʱ��
			//����ʱ��
			if((S_Strategy[(*p_Line_Num)].Time.Hours > 4)&&(UP_Min_Time<Min_Time))//��һ����������ʱ��Ҫ������һ����������ʱ��
			{
				S_Strategy[(*p_Line_Num)].Time.Hours -= 1;
			}
		}
		break;
	case STRATEGY_INFO_TIME_MINUTES:
		if((*p_Line_Num) == 0)
		{
			if(S_Strategy[(*p_Line_Num)].Time.Minutes > 0)
			{
				S_Strategy[(*p_Line_Num)].Time.Minutes -= 1;
			}
		}else{
			Min_Time = (S_Strategy[(*p_Line_Num)].Time.Hours) * 60 + S_Strategy[(*p_Line_Num)].Time.Minutes;//�������ǰ��������ʱ��
			UP_Min_Time = (S_Strategy[((*p_Line_Num)-1)].Time.Hours) * 60 + S_Strategy[((*p_Line_Num)-1)].Time.Minutes;//��һ����������ʱ��
			if((S_Strategy[(*p_Line_Num)].Time.Minutes > 0)&&(UP_Min_Time<Min_Time))
			{
				S_Strategy[(*p_Line_Num)].Time.Minutes -= 1;
			}
		}
		break;
	case STRATEGY_INFO_ROUTE_4:
		if((S_Strategy[(*p_Line_Num)].Route/1000) > 0)
		{
			S_Strategy[(*p_Line_Num)].Route -= 1000;
		}
		break;
	case STRATEGY_INFO_ROUTE_3:
		if((S_Strategy[(*p_Line_Num)].Route%1000/100) > 0)
		{
			S_Strategy[(*p_Line_Num)].Route -= 100;
		}
		break;
	case STRATEGY_INFO_ROUTE_2:
		if((S_Strategy[(*p_Line_Num)].Route%100/10) > 0)
		{
			S_Strategy[(*p_Line_Num)].Route -= 10;
		}
		break;
	case STRATEGY_INFO_ROUTE_1:
		if((S_Strategy[(*p_Line_Num)].Route%10) > 0)
		{
			S_Strategy[(*p_Line_Num)].Route -= 1;
		}
	case STRATEGY_INFO_MIN_TEMP:
		if((S_Strategy[(*p_Line_Num)].Temp_l) > 0)
		{
			S_Strategy[(*p_Line_Num)].Temp_l -= 1;
		}
		break;
	case STRATEGY_INFO_MAX_TEMP:
		if((S_Strategy[(*p_Line_Num)].Temp_h)>STRATEGY_INFO_TEMP_SECTION)
		{
			if((S_Strategy[(*p_Line_Num)].Temp_h)>(S_Strategy[(*p_Line_Num)].Temp_l+STRATEGY_INFO_TEMP_SECTION))//�²�������3��
			{
				S_Strategy[(*p_Line_Num)].Temp_h -= 1;
			}
		}
		break;
	case STRATEGY_INFO_SET:

		break;
	}
}
/*
 * ��ʼ�����ò�����Ϣ
 */
void LCD12864_Set_Strategy_Info_Page(uint8_t key,Line_Num* p_Line_Num)
{
	static uint8_t S_Place = STRATEGY_INFO_SWITCH;//��ǰ�ĸ�λ�����ò�����Ϣ����
	/*
	 * ����x ��24c02�ж�ȡ����
	 * */
	switch(key){
	case NULL:
		LCD12864_Set_Strategy_Info_Line1(&S_Place,p_Line_Num);
		LCD12864_Set_Strategy_Info_Line2(&S_Place,p_Line_Num);
		LCD12864_Set_Strategy_Info_Line3(&S_Place,p_Line_Num);
		LCD12864_Set_Strategy_Info_Line4(&S_Place,p_Line_Num);
		break;
	case K_1_num://���ܰ���
		switch(S_Place){
		case STRATEGY_INFO_SWITCH://�ڿ����ر�λ��
			S_Place++;
			break;
		case STRATEGY_INFO_STANDARD://�ڻ�׼λ��
			S_Place++;
			break;
		case STRATEGY_INFO_TIME_HOURS://��ʱ��Сʱλ��
			S_Place++;
			break;
		case STRATEGY_INFO_TIME_MINUTES://��ʱ�����λ��
			if(S_Strategy[(*p_Line_Num)].Strategy_Type == Strategy_Type_Route)
			{
				S_Place = STRATEGY_INFO_ROUTE_4;
			}else if(S_Strategy[(*p_Line_Num)].Strategy_Type == Strategy_Type_Temp){
				S_Place = STRATEGY_INFO_MIN_TEMP;
			}
			break;
		case STRATEGY_INFO_ROUTE_4://��ǧλλ��
			S_Place++;
			break;
		case STRATEGY_INFO_ROUTE_3://�ڰ�λλ��
			S_Place++;
			break;
		case STRATEGY_INFO_ROUTE_2://��ʮλλ��
			S_Place++;
			break;
		case STRATEGY_INFO_ROUTE_1://�ڸ�λλ��
			S_Place = STRATEGY_INFO_SET;
			break;
		case STRATEGY_INFO_MIN_TEMP:
			S_Place = STRATEGY_INFO_MAX_TEMP;
			break;
		case STRATEGY_INFO_MAX_TEMP:
			S_Place = STRATEGY_INFO_SET;
			break;
		case STRATEGY_INFO_SET://�ڿ����ر�λ��
			S_Place = STRATEGY_INFO_SWITCH;
			break;
		}
		LCD12864_Set_Strategy_Info_Refresh(&S_Place,p_Line_Num);
		break;
	case K_2_num://���ϰ���
		LCD12864_Set_Strategy_Info_Up_Key_Opt(&S_Place,p_Line_Num);
		LCD12864_Set_Strategy_Info_Refresh(&S_Place,p_Line_Num);
		break;
	case K_3_num://���°���
		LCD12864_Set_Strategy_Info_Down_Key_Opt(&S_Place,p_Line_Num);
		LCD12864_Set_Strategy_Info_Refresh(&S_Place,p_Line_Num);
		break;
	case K_4_num://ȡ������
		if(Now_page == Strategy_Menu_Info_page){
			//���ز��ԵĲ˵�����
			LCD12864_Display(0x00,0x00);//����
			LCD12864_Set_Strategy_Menu(NULL);
			memcpy((uint8_t*)S_Strategy,(uint8_t*)G_Strategy,sizeof(S_Strategy));
			Now_page = Strategy_Menu;

			//Strategy_this_line = Line1;
			S_Place = STRATEGY_INFO_SWITCH;
			vTaskResume(Start_LCD12864_Set_Strategy_TaskHandle);//�ָ�����
			G_Delete_Task_struct.D_Task = Start_LCD12864_Set_Strategy_Info_TaskHandle;
			Start_LCD12864_Set_Strategy_Info_TaskHandle = NULL;
			G_Delete_Task_struct.sign = ENABLE;
		}
		break;
	}
}

/*
 * ��������������Ϣ���Ĳ���
 * */
void Start_LCD12864_Set_Strategy_Info_Task(void const * argument)
{
	BaseType_t err;
	uint32_t NotifyValue;
	LCD12864_Display(0x00,0x00);//��ս���
	LCD12864_Set_Strategy_Info_Page(NULL,((Line_Num*)argument));//��ʼ��������ָ����
//	printf("argument = %d\r\n",*((Line_Num*)argument));
	while(1)
	{
		err = xTaskNotifyWait((uint32_t)0x00,			//2 �ȴ�������Ϣ
					(uint32_t)0xffffffff,
					(uint32_t*)&NotifyValue,
					(TickType_t)portMAX_DELAY);
		if(err==pdTRUE)
		{
			LCD12864_Set_Strategy_Info_Page((uint8_t)NotifyValue,((Line_Num*)argument));
		}
	}
}
/*
 * ������Ϣ��1��
 * ����X ����/�ر�
 */
void LCD12864_Set_Strategy_Info_Line1(uint8_t* p_Place,Line_Num* p_Line_Num)
{
	LCD12864_Put_16_16_Char(0xB7,0x04,0x00,WHITE_BASE);	//����
	LCD12864_Put_16_16_Char(0xB7,0x14,0x01,WHITE_BASE);	//����
	LCD12864_Put_8_16_Char(0xB7,0x24,(*p_Line_Num)+0x31,WHITE_BASE);	//NUM��
	if(S_Strategy[(*p_Line_Num)].Strategy_State == Strategy_Open)
	{
		LCD12864_Put_16_16_Char(0xB7,0x34,0x24,(*p_Place)==STRATEGY_INFO_SWITCH);	// ������
		LCD12864_Put_16_16_Char(0xB7,0x44,0x30,(*p_Place)==STRATEGY_INFO_SWITCH);
	}else{
		LCD12864_Put_16_16_Char(0xB7,0x34,0x25,(*p_Place)==STRATEGY_INFO_SWITCH);	// �ر���
		LCD12864_Put_16_16_Char(0xB7,0x44,0x31,(*p_Place)==STRATEGY_INFO_SWITCH);
	}
	LCD12864_Put_16_16_Char(0xB7,0x64,0x02,(*p_Place)==STRATEGY_INFO_SET);	//����������
	LCD12864_Put_16_16_Char(0xB7,0x74,0x03,(*p_Place)==STRATEGY_INFO_SET);
}
/*
 * ������Ϣ��2��
 */
void LCD12864_Set_Strategy_Info_Line2(uint8_t* p_Place,Line_Num* p_Line_Num)
{
	LCD12864_Put_16_16_Char(0xB5,0x04,0x32,WHITE_BASE);	//����
	LCD12864_Put_16_16_Char(0xB5,0x14,0x14,WHITE_BASE);	//׼��
	LCD12864_Put_8_16_Char(0xB5,0x24,':',WHITE_BASE);	//:��
	if(S_Strategy[(*p_Line_Num)].Strategy_Type == Strategy_Type_Route)
	{
		LCD12864_Put_16_16_Char(0xB5,0x34,0x22,(*p_Place)==STRATEGY_INFO_STANDARD);	// �����
		LCD12864_Put_16_16_Char(0xB5,0x44,0x23,(*p_Place)==STRATEGY_INFO_STANDARD);
	}else{
		LCD12864_Put_16_16_Char(0xB5,0x34,0x0A,(*p_Place)==STRATEGY_INFO_STANDARD);	// �¶���
		LCD12864_Put_16_16_Char(0xB5,0x44,0x0B,(*p_Place)==STRATEGY_INFO_STANDARD);
	}
}
/*
 * ������Ϣ��3��
 */
void LCD12864_Set_Strategy_Info_Line3(uint8_t* p_Place,Line_Num* p_Line_Num)
{
	char Hours[3];
	char Minutes[3];

	sprintf(Hours,"%02d",S_Strategy[(*p_Line_Num)].Time.Hours);
	sprintf(Minutes,"%02d",S_Strategy[(*p_Line_Num)].Time.Minutes);

	LCD12864_Put_16_16_Char(0xB3,0x04,0x0F,WHITE_BASE);	//ʱ��
	LCD12864_Put_16_16_Char(0xB3,0x14,0x12,WHITE_BASE);	//����
	LCD12864_Put_8_16_Char(0xB3,0x24,':',WHITE_BASE);	//:��

	LCD12864_Put_8_16_Char(0xB3,0x34,Hours[0],(*p_Place)==STRATEGY_INFO_TIME_HOURS);	//��
	LCD12864_Put_8_16_Char(0xB3,0x3C,Hours[1],(*p_Place)==STRATEGY_INFO_TIME_HOURS);
	LCD12864_Put_8_16_Char(0xB3,0x44,':',WHITE_BASE);	//:��
	LCD12864_Put_8_16_Char(0xB3,0x4C,Minutes[0],(*p_Place)==STRATEGY_INFO_TIME_MINUTES);
	LCD12864_Put_8_16_Char(0xB3,0x54,Minutes[1],(*p_Place)==STRATEGY_INFO_TIME_MINUTES);
}
/*
 * ������Ϣ��4��
 */
void LCD12864_Set_Strategy_Info_Line4(uint8_t* p_Place,Line_Num* p_Line_Num)
{
	char Route[5];
	char Min_Temp[3];
	char Max_Temp[3];
	if(S_Strategy[(*p_Line_Num)].Strategy_Type == Strategy_Type_Route)
	{
		sprintf(Route,"%04d",S_Strategy[(*p_Line_Num)].Route);
		LCD12864_Put_16_16_Char(0xB1,0x04,0x22,WHITE_BASE);	//����
		LCD12864_Put_16_16_Char(0xB1,0x14,0x23,WHITE_BASE);	//����
		LCD12864_Put_8_16_Char(0xB1,0x24,':',WHITE_BASE);	//:��
		LCD12864_Put_8_16_Char(0xB1,0x34,Route[0],(*p_Place)==STRATEGY_INFO_ROUTE_4);	// ���/�¶���
		LCD12864_Put_8_16_Char(0xB1,0x3C,Route[1],(*p_Place)==STRATEGY_INFO_ROUTE_3);
		LCD12864_Put_8_16_Char(0xB1,0x44,Route[2],(*p_Place)==STRATEGY_INFO_ROUTE_2);	//:��
		LCD12864_Put_8_16_Char(0xB1,0x4C,Route[3],(*p_Place)==STRATEGY_INFO_ROUTE_1);	// ���/�¶���
		LCD12864_Put_16_16_Char(0xB1,0x54,0x2D,WHITE_BASE);	//��շ���
		LCD12864_Put_16_16_Char(0xB1,0x64,0x2D,WHITE_BASE);	//
		LCD12864_Put_16_16_Char(0xB1,0x74,0x2D,WHITE_BASE);	//
	}else if(S_Strategy[(*p_Line_Num)].Strategy_Type == Strategy_Type_Temp){
		sprintf(Min_Temp,"%02d",S_Strategy[(*p_Line_Num)].Temp_l);
		sprintf(Max_Temp,"%02d",S_Strategy[(*p_Line_Num)].Temp_h);
		LCD12864_Put_16_16_Char(0xB1,0x04,0x0A,WHITE_BASE);	//����
		LCD12864_Put_16_16_Char(0xB1,0x14,0x0B,WHITE_BASE);	//����
		LCD12864_Put_8_16_Char(0xB1,0x24,':',WHITE_BASE);	//:��
		LCD12864_Put_8_16_Char(0xB1,0x34,Min_Temp[0],(*p_Place)==STRATEGY_INFO_MIN_TEMP);	//
		LCD12864_Put_8_16_Char(0xB1,0x3C,Min_Temp[1],(*p_Place)==STRATEGY_INFO_MIN_TEMP);
		LCD12864_Put_16_16_Char(0xB1,0x44,0x2F,WHITE_BASE);	//����
		LCD12864_Put_8_16_Char(0xB1,0x54,'-',WHITE_BASE);	//--
		LCD12864_Put_8_16_Char(0xB1,0x5c,'-',WHITE_BASE);
		LCD12864_Put_8_16_Char(0xB1,0x64,Max_Temp[0],(*p_Place)==STRATEGY_INFO_MAX_TEMP);	//��
		LCD12864_Put_8_16_Char(0xB1,0x6C,Max_Temp[1],(*p_Place)==STRATEGY_INFO_MAX_TEMP);	//
		LCD12864_Put_16_16_Char(0xB1,0x74,0x2F,WHITE_BASE);	//����
	}
}
