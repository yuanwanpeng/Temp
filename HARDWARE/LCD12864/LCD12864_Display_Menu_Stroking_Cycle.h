/*
 * LCD12864_Display_Menu_Set_Time.h
 *
 *  Created on: 2018Äê10ÔÂ22ÈÕ
 *      Author: YuanWP
 */

#ifndef HARDWARE_LCD12864_LCD12864_DISPLAY_MENU_STROKING_CYCLE_H_
#define HARDWARE_LCD12864_LCD12864_DISPLAY_MENU_STROKING_CYCLE_H_

#include "main.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "LCD12864.h"
#include "stdint.h"
#include "relay.h"

extern osThreadId Start_LCD12864_Stroking_Cycle_TaskHandle;

void Start_LCD12864_Stroking_Cycle_Task(void const * argument);
void LCD12864_Display_Stroking_Cycle_Page(uint8_t key);
void LCD12864_Display_Stroking_Cycle_Interior(uint8_t* p_S_Stroking_Cycle);
void LCD12864_Display_Stroking_Cycle_Refresh(uint8_t* p_S_Stroking_Cycle);


#endif /* HARDWARE_LCD12864_LCD12864_DISPLAY_MENU_SET_TIME_H_ */
