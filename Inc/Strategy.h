/*
 * Strategy.h
 *
 *  Created on: 2018��11��28��
 *      Author: YuanWP
 */

#ifndef INC_STRATEGY_H_
#define INC_STRATEGY_H_
#include "LCD12864_Display_Menu_Delay_Inspection.h"
extern uint8_t G_Delay_Inspection;
extern Strategy_struct S_Strategy[8];	//8������

void Init_Strategy(uint8_t num);		//��ʼ������
void Start_Strategy_Task(void const * argument);//ִ�в�������


#endif /* INC_STRATEGY_H_ */
