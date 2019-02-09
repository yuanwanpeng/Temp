/*
 * uart.h
 *
 *  Created on: 2018Äê7ÔÂ24ÈÕ
 *      Author: Administrator
 */

#ifndef INC_UART_H_
#define INC_UART_H_
#include "stdint.h"
#include <string.h>
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "main.h"
#include "dma.h"
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart1;
void Send_To_Uart2_Str(int8_t* str,uint32_t len);

#endif /* INC_UART_H_ */


