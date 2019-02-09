/*
 * ESP8266.h
 *
 *  Created on: 2018��9��5��
 *      Author: YuanWP
 */

#ifndef HARDWARE_ESP8266_ESP8266_H_
#define HARDWARE_ESP8266_ESP8266_H_

#include "stdint.h"
#include "stdio.h"
#include "button.h"
#include <string.h>
//#include <jansson.h>
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "main.h"
#include "uart.h"
#include "HTTP_CODE.h"
#define AT		"AT\r\n"
#define SET_AT_CWSTARTSMART	"AT+CWSTARTSMART\r\n"
#define SET_AT_CWMODE_1 	"AT+CWMODE=1\r\n"//���õ�ǰ Wi-Fi ģʽ�����浽 1��Station ģʽ  2��SoftAP ģʽ 3��SoftAP+Station ģʽ
#define AT_RST				"AT+RST\r\n"
#define	GET_AT_CIFSR		"AT+CIFSR\r\n"	//��ѯ�豸ip��ַ
#define SET_AT_CIPSTART		"AT+CIPSTART=\"TCP\",\"183.230.40.39\",876\r\n"
#define SET_AT_CIPMODE_1    "AT+CIPMODE=1\r\n"		//͸��ģʽ
#define SET_AT_CIPSEND     	"AT+CIPSEND\r\n"
#define GET_AT_CIPSTATUS   "AT+CIPSTATUS\r\n"
#define SET_AT_CWJAP_DEF  	"AT+ =\"Fighting...0\",\"yuanwanpeng\"\r\n"			//���� AP�����浽 Flash

#define CHECK_AT			"AT\r\n"
#define SET_AT_CWSTARTSMART	"AT+CWSTARTSMART\r\n"


#define   MAX_SEND_BUF_LEN  512

extern UART_HandleTypeDef huart3;
extern osThreadId Start_ESP8266_TaskHandle;


void SendCmd(int8_t* cmd, int8_t* result, uint16_t timeOut);
void Start_ESP8266_Task(void const * argument);
void AT_CIPSTART_COM(void);// ����TCP
void AT_CIFSR(void);
void AT_RST_COM(void);
void AT_COM(void);
int16_t ESP8266_CheckStatus(int16_t timeOut);
void AT_CWMODE(void);
void AT_CWSTARTSMART(void);
void Send_To_Uart2_Str(int8_t* str,uint32_t len);

#endif /* HARDWARE_ESP8266_ESP8266_H_ */
