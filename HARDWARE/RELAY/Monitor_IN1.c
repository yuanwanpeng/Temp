/*
 * Monitor_IN1.c
 *
 *  Created on: 2018��10��25��
 *      Author: YuanWP
 */
#include "Monitor_IN1.h"

uint8_t G_Beyond_Route_Mask;

void Start_Monitor_IN1_Task(void const * argument)//��ʼ�г����ڼ������
{
	uint8_t relay1,relay2,In_State;
	while(1)
	{
		relay1 = RELAY1_STATE;
		relay2 = RELAY2_STATE;
		In_State = IN1_STATE;
		if(In_State==1)					//��ʼʱ�����0  ����ת��1
		{
			if(relay1==0)				//��ʾ�̵���1������ ��ת
			{
				while(In_State)			//�ж����Ȳ�����0
				{
					osDelay(100);
					In_State = IN1_STATE;
				}
				G_Now_Route++;			//�г̼�һȦ
				if((G_Now_Route == G_Max_Route)&&(G_New_Mode != 0))//��ǰ�г̵�������г�  �Զ�ģʽ��
				{
					Motor_Stop();		//��ǰ�г̴��ڵ�������г�ֹͣת��
				}
				if((G_New_Mode == 0) && (G_Now_Route >= G_Max_Route))//���ģʽ����0 ��ʾʵ���ֶ�ģʽ�£��жϵ�ǰ�г̴��ڵ�������г���
				{
					if(G_Now_Route == G_Max_Route)
					{
						
						Motor_Stop();		//��ǰ�г̴��ڵ�������г�ֹͣת��
					}
					if(G_Beyond_Route_Mask == 0)
					{
						//G_Old_Route = G_Now_Route;//����ǰ�г̼�¼���ҵ�buff buff���г̼�5�õ�����г̺��5����λ
						G_Beyond_Route_Mask = 1;
					}
					if(G_Now_Route == (G_Old_Route+5))
					{
						G_Beyond_Route_Mask = 0;
					//	G_Old_Route = G_Now_Route;
						Motor_Stop();		//��ǰ�г̴��ڵ�������г�ֹͣת��
					}
				}
				Save_G_Now_Route(G_Now_Route);
			}else if(relay2==0)			//��ʾ�̵���2������ ��ת
			{
				while(In_State)			//�ж����Ȳ�����0
				{
					osDelay(100);
					In_State = IN1_STATE;
				}
				G_Now_Route--;			//�г̼�һȦ
				if((G_Now_Route == 0)&&(G_New_Mode != 0))	//�г̵���0ֹͣת��
				{
					Motor_Stop();		//��ǰ�г̵���0ֹͣת��
				}
				if((G_New_Mode == 0) && (G_Now_Route <= 0))//���ģʽ����0 ��ʾʵ���ֶ�ģʽ�£��жϵ�ǰ�г̴��ڵ�������г���
				{
					if(G_Now_Route == 0)
					{
						Motor_Stop();		//��ǰ�г̴��ڵ�������г�ֹͣת��
					}
					if(G_Beyond_Route_Mask == 0)
					{
						//G_Old_Route = G_Now_Route;//����ǰ�г̼�¼���ҵ�buff buff���г̼�5�õ�����г̺��5����λ
						G_Beyond_Route_Mask = 1;
					}
					if(G_Now_Route == (G_Old_Route-5))
					{
						G_Beyond_Route_Mask = 0;
					//	G_Old_Route = G_Now_Route;
						Motor_Stop();		//��ǰ�г̴��ڵ�������г�ֹͣת��
					}
				}
				Save_G_Now_Route(G_Now_Route);
			}
		}
	}
}
/*���г̼�¼���ҵ�24c02����*/
void Save_G_Now_Route(int16_t Now_Route)
{
	uint8_t Now_Route_H;
	uint8_t Now_Route_L;
	Now_Route_H = Now_Route>>8;
	Now_Route_L = Now_Route;
	AT24CXX_Write(NOW_ROUTE,&Now_Route_H,1);
	AT24CXX_Write(NOW_ROUTE+1,&Now_Route_L,1);
}

