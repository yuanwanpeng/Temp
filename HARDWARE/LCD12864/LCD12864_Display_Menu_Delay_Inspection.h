/*
 * LCD12864_Display_Menu_Delay_Inspection.h
 *
 *  Created on: 2018Äê10ÔÂ22ÈÕ
 *      Author: YuanWP
 */

#ifndef HARDWARE_LCD12864_LCD12864_DISPLAY_MENU_DELAY_INSPECTION_H_
#define HARDWARE_LCD12864_LCD12864_DISPLAY_MENU_DELAY_INSPECTION_H_

#include "main.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "LCD12864.h"
#include "stdint.h"
#include "relay.h"
extern osThreadId Start_LCD12864_Delay_Inspection_TaskHandle;

void Start_LCD12864_Delay_Inspection_Task(void const * argument);
void LCD12864_Display_Delay_Inspection_Page(uint8_t key);
void LCD12864_Display_Delay_Inspection_Interior(uint8_t* p_S_Delay_Inspection,uint8_t* p_Coordinate);
void LCD12864_Display_Delay_Inspection_Refresh(uint8_t* p_S_Delay_Inspection,uint8_t* p_Coordinate);


#endif /* HARDWARE_LCD12864_LCD12864_DISPLAY_MENU_DELAY_INSPECTION_H_ */
