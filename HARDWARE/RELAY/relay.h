/*
 * relay.h
 *
 *  Created on: 2018年7月25日
 *      Author: YuanWP
 */

#ifndef HARDWARE_RELAY_RELAY_H_
#define HARDWARE_RELAY_RELAY_H_
#include "stdint.h"
#include "button.h"

#define MAX_ROUTE	0x82
#define NOW_ROUTE	0x84
#define STORKING_CYCLE	0x87

#define RELAY1_ENABLE 	HAL_GPIO_WritePin(OUTC1_GPIO_Port, OUTC1_Pin, GPIO_PIN_RESET);
#define RELAY1_DISABLE 	HAL_GPIO_WritePin(OUTC1_GPIO_Port, OUTC1_Pin, GPIO_PIN_SET);
#define RELAY1_STATE 	HAL_GPIO_ReadPin(OUTC1_GPIO_Port, OUTC1_Pin);

#define RELAY2_ENABLE 	HAL_GPIO_WritePin(OUTC2_GPIO_Port, OUTC2_Pin, GPIO_PIN_RESET);
#define RELAY2_DISABLE 	HAL_GPIO_WritePin(OUTC2_GPIO_Port, OUTC2_Pin, GPIO_PIN_SET);
#define RELAY2_STATE 	HAL_GPIO_ReadPin(OUTC2_GPIO_Port, OUTC2_Pin);


extern uint16_t G_Max_Route;
extern int16_t G_Now_Route;//当前行程
extern int16_t G_Old_Route;
extern uint8_t G_Stroking_Cycle;//行程周期
extern osThreadId Start_Relay_TaskHandle;
/*
 *  运行继电器
 *
 */
void Check_Max_And_Now_Route(void);
void Init_Max_Route(uint16_t Max_Route);
void Init_Now_Route(int16_t Now_Route);
void Start_Relay_Task(void const * argument);
void G_Route_Reset(void);
void Relay_key_Opt(uint8_t key);
void Motor_Forward(void);
void Motor_Reverses(void);
void Motor_Stop(void);
void Check_Stroking_Cycle(void);
void Init_Stroking_Cycle(uint8_t Stroking_Cycle);
#endif /* HARDWARE_RELAY_RELAY_H_ */
