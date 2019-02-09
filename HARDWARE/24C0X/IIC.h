/*
 * 24c0x.h
 *
 *  Created on: 2018��10��16��
 *      Author: YuanWP
 */

#ifndef HARDWARE_24C0X_IIC_H_
#define HARDWARE_24C0X_IIC_H_
#include "main.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "stdint.h"
#include "delay.h"
#define IIC_SDA_H (HAL_GPIO_WritePin(SDA_24C0X_GPIO_Port, SDA_24C0X_Pin, GPIO_PIN_SET))
#define IIC_SDA_L (HAL_GPIO_WritePin(SDA_24C0X_GPIO_Port, SDA_24C0X_Pin, GPIO_PIN_RESET))
#define IIC_SCL_H (HAL_GPIO_WritePin(SCL_24C0X_GPIO_Port, SCL_24C0X_Pin, GPIO_PIN_SET))
#define IIC_SCL_L (HAL_GPIO_WritePin(SCL_24C0X_GPIO_Port, SCL_24C0X_Pin, GPIO_PIN_RESET))



//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(uint8_t txd);			//IIC����һ���ֽ�
uint8_t IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
uint8_t IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);

#endif /* HARDWARE_24C0X_IIC_H_ */
