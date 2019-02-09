/*
 * 24c0x.h
 *
 *  Created on: 2018年10月16日
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



//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(uint8_t txd);			//IIC发送一个字节
uint8_t IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
uint8_t IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);

#endif /* HARDWARE_24C0X_IIC_H_ */
