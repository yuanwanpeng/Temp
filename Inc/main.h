/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#include "stdint.h"
/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define OUTC2_Pin GPIO_PIN_0
#define OUTC2_GPIO_Port GPIOA
#define OUTC3_Pin GPIO_PIN_1
#define OUTC3_GPIO_Port GPIOA
#define USART2_TX_8266_Pin GPIO_PIN_2
#define USART2_TX_8266_GPIO_Port GPIOA
#define USART2_RX_8266_Pin GPIO_PIN_3
#define USART2_RX_8266_GPIO_Port GPIOA
#define IN1_Pin GPIO_PIN_4
#define IN1_GPIO_Port GPIOA
#define OUTC1_Pin GPIO_PIN_5
#define OUTC1_GPIO_Port GPIOA
#define B_IN3_Pin GPIO_PIN_6
#define B_IN3_GPIO_Port GPIOA
#define B_IN4_Pin GPIO_PIN_7
#define B_IN4_GPIO_Port GPIOA
#define Buzzer_Pin GPIO_PIN_12
#define Buzzer_GPIO_Port GPIOB
#define UPCi_Pin GPIO_PIN_13
#define UPCi_GPIO_Port GPIOB
#define SCL_24C0X_Pin GPIO_PIN_15
#define SCL_24C0X_GPIO_Port GPIOB
#define SDA_24C0X_Pin GPIO_PIN_8
#define SDA_24C0X_GPIO_Port GPIOA
#define MCU_RUN_LED_Pin GPIO_PIN_11
#define MCU_RUN_LED_GPIO_Port GPIOA
#define MCU_ALARM_LED_Pin GPIO_PIN_12
#define MCU_ALARM_LED_GPIO_Port GPIOA
#define PWKEY_CTL_Pin GPIO_PIN_15
#define PWKEY_CTL_GPIO_Port GPIOA
#define CS_LCD_Pin GPIO_PIN_3
#define CS_LCD_GPIO_Port GPIOB
#define RST_LCD_Pin GPIO_PIN_4
#define RST_LCD_GPIO_Port GPIOB
#define A0_LCD_Pin GPIO_PIN_5
#define A0_LCD_GPIO_Port GPIOB
#define SCL_LCD_Pin GPIO_PIN_6
#define SCL_LCD_GPIO_Port GPIOB
#define SDA_LCD_Pin GPIO_PIN_7
#define SDA_LCD_GPIO_Port GPIOB
#define B_IN1_Pin GPIO_PIN_8
#define B_IN1_GPIO_Port GPIOB
#define B_IN2_Pin GPIO_PIN_9
#define B_IN2_GPIO_Port GPIOB

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */

typedef enum{
	Line1 = 0,
	Line2 = 1,
	Line3 = 2,
	Line4 = 3,
	Line5 = 4,
	Line6 = 5,
	Line7 = 6,
	Line8 = 7,
}Line_Num;

//typedef struct{
//	uint8_t sign;//标志为0不删除，标志位1，就给我删除我艹
//	osThreadId D_Task;
//}Delete_Task_struct;



void Init_Strategy(uint8_t num);
/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
