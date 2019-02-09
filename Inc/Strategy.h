/*
 * Strategy.h
 *
 *  Created on: 2018年11月28日
 *      Author: YuanWP
 */

#ifndef INC_STRATEGY_H_
#define INC_STRATEGY_H_
#include "LCD12864_Display_Menu_Delay_Inspection.h"
extern uint8_t G_Delay_Inspection;
extern Strategy_struct S_Strategy[8];	//8条策略

void Init_Strategy(uint8_t num);		//初始化策略
void Start_Strategy_Task(void const * argument);//执行策略任务


#endif /* INC_STRATEGY_H_ */
