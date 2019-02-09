/*
 * button.c
 *
 *  Created on: 2018��7��24��
 *      Author: YuanWP
 */
#include "button.h"
#include "BUZZER.h"
#include "queue.h"
#include "Check_Stroking_Cycle.h"
#include "cmsis_os.h"
#define SHAKE_TIME 			50			//��������ʱ��
#define SCAN_BUTTON_SIZE	64			//ɨ�谴�������ջ��С
#define BUTTON_EXE_SIZE		128			//ִ�н���ɨ�谴�������ջ��С
osThreadId ScanButtonTaskHandle;		//ɨ�谴����������
osThreadId ButtonExeTaskHandle;			//����ɨ�谴���ļ�ֵ�����͸�ִ�������������
extern osThreadId Start_LCD12864_TaskHandle;	//��ʼ12864��������
extern osThreadId defaultTaskHandle;		//��ʼ������
QueueHandle_t xQueue1;					//��Ϣ���о��(�Ѿ����滻)

/*
 * ��ʼ������������
 */
void Start_Button_Task(void const * argument)
{
	osThreadDef(ScanButtonTask, Scan_Button_Task, osPriorityNormal, 0, SCAN_BUTTON_SIZE);	//ɨ�� key����׼��
	ScanButtonTaskHandle = osThreadCreate(osThread(ScanButtonTask), NULL);	//����ɨ�� key���񴴽�

	osThreadDef(ButtonExeTask, Button_Exe_Task, osPriorityNormal, 0, BUTTON_EXE_SIZE);	//����ִ����KEYɨ�������ͨ��xTaskNotifyWait������ȡ��ֵ
	ButtonExeTaskHandle = osThreadCreate(osThread(ButtonExeTask), NULL);	//��������KEYֵ������Start_LCD12864_TaskHandle���͵����������

	while(1)
	{
	}
}
/*
 *    ɨ�� key
 */
void Scan_Button_Task(void const * argument)
{
	BaseType_t err;
	uint16_t touch_time = 0;
	uint8_t touch_mark = 0;
//	HAL_GPIO_WritePin(GPIOA, PWKEY_CTL_Pin, GPIO_PIN_RESET);//����SIM800C
	osDelay(6000);
//	HAL_GPIO_WritePin(GPIOA, PWKEY_CTL_Pin, GPIO_PIN_SET);
	osThreadTerminate(defaultTaskHandle);		//ɾ����ʼ����
	osThreadTerminate(Start_BUTTON_TaskHandle);	//ɾ��������������ĺ���

	while(1)
	{
		if(BUTTON1==0)
		{
			osDelay(SHAKE_TIME);
			if(BUTTON1==0)
			{
				while(BUTTON1==0){
					osDelay(SHAKE_TIME);
				}
				if(ButtonExeTaskHandle!=NULL)
				{
					xTaskNotify((TaskHandle_t)ButtonExeTaskHandle,
							(uint32_t)K_1_num,
							(eNotifyAction)eSetValueWithOverwrite);
				}
			}	//�����źŰ��� ѡ�� ����
		}
		if(BUTTON2==0)
		{
			osDelay(SHAKE_TIME);
			if(BUTTON2==0)
			{
				while(BUTTON2==0){
					osDelay(SHAKE_TIME);
					if(touch_time<(TOUCH_TIME+10))
						touch_time++;
					if((touch_time >= TOUCH_TIME)&&(touch_mark==0)){
						touch_mark = 1;//���ñ�־λ
						xTaskNotify((TaskHandle_t)ButtonExeTaskHandle,
								(uint32_t)K_2_num_long,
								(eNotifyAction)eSetValueWithOverwrite);
					}
				}
				if((ButtonExeTaskHandle!=NULL)&&(touch_time < TOUCH_TIME))
				{
					xTaskNotify((TaskHandle_t)ButtonExeTaskHandle,
							(uint32_t)K_2_num,
							(eNotifyAction)eSetValueWithOverwrite);
				}
				touch_time = 0;
				touch_mark = 0;//���ñ�־λ
			}	//�����źŰ��� �� ����
		}
		if(BUTTON3==0)
		{
			osDelay(SHAKE_TIME);
			if(BUTTON3==0)
			{
				while(BUTTON3==0){
					osDelay(SHAKE_TIME);
					if(touch_time<(TOUCH_TIME+10))
						touch_time++;
					if((touch_time >= TOUCH_TIME)&&(touch_mark==0)){
						touch_mark = 1;//���ñ�־λ
						xTaskNotify((TaskHandle_t)ButtonExeTaskHandle,
								(uint32_t)K_3_num_long,
								(eNotifyAction)eSetValueWithOverwrite);
					}
				}
				if((ButtonExeTaskHandle!=NULL)&&(touch_time < TOUCH_TIME))
				{
					xTaskNotify((TaskHandle_t)ButtonExeTaskHandle,
							(uint32_t)K_3_num,
							(eNotifyAction)eSetValueWithOverwrite);
				}
				touch_time = 0;
				touch_mark = 0;//���ñ�־λ
			}	//�����źŰ��� �� ����
		}
		if(BUTTON4==0)
		{
			osDelay(SHAKE_TIME);
			if(BUTTON4==0)
			{
				while(BUTTON4==0){
					osDelay(SHAKE_TIME);
					if(touch_time<(TOUCH_TIME+10))
						touch_time++;
					if((touch_time >= TOUCH_TIME)&&(touch_mark==0)){
						touch_mark = 1;//���ñ�־λ
						xTaskNotify((TaskHandle_t)ButtonExeTaskHandle,
								(uint32_t)K_4_num_long,
								(eNotifyAction)eSetValueWithOverwrite);
					}
				}
				if((ButtonExeTaskHandle!=NULL)&&(touch_time < TOUCH_TIME))
				{
					err = xTaskNotify((TaskHandle_t)ButtonExeTaskHandle,
							(uint32_t)K_4_num,
							(eNotifyAction)eSetValueWithOverwrite);
				}
				touch_time = 0;
				touch_mark = 0;//���ñ�־λ
			}	//�����źŰ��� ȡ�� ����
		}
		if(err==pdFAIL)
		{
			printf("1 send key value false\r\n");
		}
	}
}

void Button_Exe_Task(void const * argument)
{
	BaseType_t err;
	uint32_t NotifyValue;
	while(1)
	{
		err = xTaskNotifyWait((uint32_t)0x00,
				(uint32_t)0xffffffff,
				(uint32_t*)&NotifyValue,
				(TickType_t)portMAX_DELAY);
		if(err==pdTRUE)
		{
			switch((uint8_t)NotifyValue){
			case K_1_num:
		//		printf("���ܰ���\r\n");//��ӡ����
				Buzzer_ONE_Cycle();
				if(Start_LCD12864_TaskHandle!=NULL)
				{
					xTaskNotify((TaskHandle_t)Start_LCD12864_TaskHandle,
							(uint32_t)K_1_num,
							(eNotifyAction)eSetValueWithOverwrite);//�����źŰ��� ѡ�� ����
					if(err==pdFAIL)
					{
						printf("2 send key value false\r\n");
					}
				}
				break;
			case K_2_num:
		//		printf("���ϰ���\r\n");//��ӡ����
				Buzzer_ONE_Cycle();
				if(Start_LCD12864_TaskHandle!=NULL)
				{
					xTaskNotify((TaskHandle_t)Start_LCD12864_TaskHandle,
							(uint32_t)K_2_num,
							(eNotifyAction)eSetValueWithOverwrite);//�����źŰ��� �� ����
					if(err==pdFAIL)
					{
						printf("2 send key value false\r\n");
					}
				}
				break;
			case K_3_num:
		//		printf("���°���\r\n");//��ӡ����
				Buzzer_ONE_Cycle();
				if(Start_LCD12864_TaskHandle!=NULL)
				{
					xTaskNotify((TaskHandle_t)Start_LCD12864_TaskHandle,
							(uint32_t)K_3_num,
							(eNotifyAction)eSetValueWithOverwrite);//�����źŰ��� �� ����
					if(err==pdFAIL)
					{
						printf("2 send key value false\r\n");
					}
				}
				break;
			case K_4_num:
		//		printf("ȡ������\r\n");//��ӡ����
				Buzzer_ONE_Cycle();	//��������һ��
				if(Start_LCD12864_TaskHandle!=NULL)
				{
					err = xTaskNotify((TaskHandle_t)Start_LCD12864_TaskHandle,
							(uint32_t)K_4_num,
							(eNotifyAction)eSetValueWithOverwrite);//�����źŰ��� ȡ�� ����
					if(err==pdFAIL)
					{
						printf("2 send key value false\r\n");
					}
				}
				break;
			case K_2_num_long:
		//		printf("���ϰ�������\r\n");//��ӡ����
				Buzzer_TWO_Cycle();		//����������һ��
				err = xTaskNotify((TaskHandle_t)Start_LCD12864_TaskHandle,
						(uint32_t)K_2_num_long,
						(eNotifyAction)eSetValueWithOverwrite);
				if(err==pdFAIL)
				{
					printf("2 send key value false\r\n");
				}
				break;
			case K_3_num_long:
		//		printf("���°�������\r\n");//��ӡ����
				Buzzer_TWO_Cycle();		//����������һ��
				err = xTaskNotify((TaskHandle_t)Start_LCD12864_TaskHandle,
					(uint32_t)K_3_num_long,
					(eNotifyAction)eSetValueWithOverwrite);
				if(err==pdFAIL)
				{
					printf("2 send key value false\r\n");
				}
				break;
			case K_4_num_long:
				//printf("ȡ����������\r\n");//��ӡ����
				Buzzer_TWO_Cycle();		//����������һ��
				err = xTaskNotify((TaskHandle_t)Start_LCD12864_TaskHandle,
					(uint32_t)K_4_num_long,
					(eNotifyAction)eSetValueWithOverwrite);
				if(err==pdFAIL)
				{
					printf("2 send key value false\r\n");
				}
				break;
			}
		}
	}
}



