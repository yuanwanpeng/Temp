/*
 * 24c0x.h
 *
 *  Created on: 2018��10��16��
 *      Author: YuanWP
 */

#ifndef HARDWARE_24C0X_24C0X_H_
#define HARDWARE_24C0X_24C0X_H_
#include "main.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "stdint.h"
#include "delay.h"
#include "LCD12864_Display_Menu_Set_Strategy.h"
#define AT24C01		127
#define AT24C02		255
#define AT24C04		511
#define AT24C08		1023
#define AT24C16		2047
#define AT24C32		4095
#define AT24C64	    8191
#define AT24C128	16383
#define AT24C256	32767
//Mini STM32������ʹ�õ���24c02�����Զ���EE_TYPEΪAT24C02
#define EE_TYPE AT24C02

#define DELAY_INSPECTION	0x86

extern uint8_t G_Delay_Inspection;

void AT24CXX_Init(void);
void AT24CXX_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite);
uint8_t AT24CXX_ReadOneByte(uint16_t ReadAddr);
void AT24CXX_WriteLenByte(uint16_t WriteAddr,uint32_t DataToWrite,uint8_t Len);	//ָ����ַ��ʼд��ָ�����ȵ�����
uint32_t AT24CXX_ReadLenByte(uint16_t ReadAddr,uint8_t Len);					//ָ����ַ��ʼ��ȡָ����������
void AT24CXX_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite);	//��ָ����ַ��ʼд��ָ�����ȵ�����
void AT24CXX_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead);   	//��ָ����ַ��ʼ����ָ�����ȵ�����

void Check_Delay_Inspection(void);
void Init_Delay_Inspection(uint8_t Delay_Inspection);
#endif /* HARDWARE_24C0X_24C0X_H_ */

