/*
 * Check_Stroking_Cycle.c
 *
 *  Created on: 2018��10��25��
 *      Author: YuanWP
 */
#include "Check_Stroking_Cycle.h"
#include "main.h"
#include "cmsis_os.h"
#include "stm32f1xx_hal.h"
#include "relay.h"
#include "24c0x.h"
#include "BUZZER.h"
//TimerHandle_t Stroking_Cycle_Timer01Handle;
/*
 * ��ʼ�г����ڼ������
 */
void Start_Check_Stroking_Cycle_Task(void const * argument)
{
	uint8_t relay1,relay2;
	static uint16_t Time = 0;
	int16_t Old_G_Now_Route = G_Now_Route;
	while(1)
	{
		relay1 = RELAY1_STATE;
		relay2 = RELAY2_STATE;
		if(relay1&&relay2)	//=1 ��ʾ���û����ת���߷�ת  ������ʱ��
		{
			Time = 0;
		}else{
			if((Time>G_Stroking_Cycle))
			{
				//ǿ��ֹͣת�����
				RELAY1_DISABLE;
				RELAY2_DISABLE;
				printf("�������������� û�н��ܵ�Ӧ�еĸɻɹ��ź�\r\n");//����������
				BUZZER_ENABLE;
			}else{
				Time++;			//����ʱ��
				if(G_Now_Route!=Old_G_Now_Route)//�г̲����˵������,���¼�ʱ
				{
					Time = 0;
					Old_G_Now_Route = G_Now_Route;
				}
			}
		}
		osDelay(1000);		//һ��
	}
}




//void Create_Stroking_Cycle_Timer01(void)
//{
//	taskENTER_CRITICAL();
//	Stroking_Cycle_Timer01Handle = xTimerCreate("Stroking_Cycle_Timer01",
//										(TickType_t	)100,
//										(UBaseType_t)pdTRUE,
//										(void *		)1,
//										(TimerCallbackFunction_t)Stroking_Cycle_Timer01_CallBack);
//	taskEXIT_CRITICAL();
//}
////��ʱ���Ļص�����
//void Stroking_Cycle_Timer01_CallBack(TimerHandle_t xTimer)
//{
//	printf("Stroking_Cycle_Timer01_CallBack\r\n");
//}

