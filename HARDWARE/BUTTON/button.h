/*
 * button.h
 *
 *  Created on: 2018��7��24��
 *      Author: Administrator
 */

#ifndef HARDWARE_BUTTON_BUTTON_H_
#define HARDWARE_BUTTON_BUTTON_H_

#include "main.h"
#include "FreeRTOS.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"

#define BUTTON1 HAL_GPIO_ReadPin(B_IN1_GPIO_Port, B_IN1_Pin)
#define BUTTON2 HAL_GPIO_ReadPin(B_IN2_GPIO_Port, B_IN2_Pin)
#define BUTTON3 HAL_GPIO_ReadPin(B_IN3_GPIO_Port, B_IN3_Pin)
#define BUTTON4 HAL_GPIO_ReadPin(B_IN4_GPIO_Port, B_IN4_Pin)
#define K_1_num (1<<0)
#define K_2_num (1<<1)
#define K_3_num (1<<2)
#define K_4_num (1<<3)
#define	K_2_num_long	(1<<5)
#define	K_3_num_long	(1<<6)
#define	K_4_num_long	(1<<7)
#define TOUCH_TIME (30)
struct AMessage
{
	char ucMessageID;
	char ucKey_num;
};

extern osThreadId ButtonExeTaskHandle;
extern osThreadId Start_BUTTON_TaskHandle;
/*
 *   �豸��ť��������������
 */
void Start_Button_Task(void const * argument);
/*
 * 	ɨ�谴ť����
 */
void Scan_Button_Task(void const * argument);
/*
 * ����ִ�к���
 * */
void Button_Exe_Task(void const * argument);
#endif /* HARDWARE_BUTTON_BUTTON_H_ */
