/*
 * HUMI.h
 *
 *  Created on: 2018Äê8ÔÂ14ÈÕ
 *      Author: YuanWP
 */

#ifndef HARDWARE_HUMI_HUMI_H_
#define HARDWARE_HUMI_HUMI_H_

#define HUMI_COMP	0x80

extern float Compensation;
extern float comp;
void Init_Humi_Comp(void);
void Start_HUMI_Task(void const * argument);

#endif /* HARDWARE_HUMI_HUMI_H_ */
