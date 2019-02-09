/*
 * IIC.c
 *
 *  Created on: 2018年10月16日
 *      Author: YuanWP
 */
#include "IIC.h"

#include "main.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"

/*
 *  初始化IIc
 */
void IIC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	/*Configure GPIO pins :  SCL_24C0X_Pin  */
	GPIO_InitStruct.Pin = SCL_24C0X_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pins :    SDA_24C0X_Pin                */
	GPIO_InitStruct.Pin = SDA_24C0X_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	HAL_GPIO_WritePin(SCL_24C0X_GPIO_Port, SCL_24C0X_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SDA_24C0X_GPIO_Port, SDA_24C0X_Pin,GPIO_PIN_RESET);
}
void SDA_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	/*Configure GPIO pins :    SDA_24C0X_Pin                */
	GPIO_InitStruct.Pin = SDA_24C0X_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;//上拉输出
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
void SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	/*Configure GPIO pins :    SDA_24C0X_Pin                */
	GPIO_InitStruct.Pin = SDA_24C0X_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;//上拉输出
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
//开始信号
void IIC_Start(void)
{
	SDA_OUT();
	IIC_SDA_H;
	IIC_SCL_H;
	delay_us(4);
	IIC_SDA_L;
	delay_us(4);
	IIC_SCL_L;
}
//停止信号
void IIC_Stop(void)
{
	SDA_OUT();//sda设置输出
	IIC_SCL_L;
	IIC_SDA_L;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
 	IIC_SCL_H;
 	IIC_SDA_H;
	delay_us(4);
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	SDA_IN();      //SDA设置为输入
	IIC_SDA_H;delay_us(1);
	IIC_SCL_H;delay_us(1);
	while(HAL_GPIO_ReadPin(SDA_24C0X_GPIO_Port, SDA_24C0X_Pin))
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL_L;//时钟输出0
	return 0;
}
//产生ACK应答
void IIC_Ack(void)
{
	IIC_SCL_L;
	SDA_OUT();
	IIC_SDA_L;
	delay_us(2);
	IIC_SCL_H;
	delay_us(2);
	IIC_SCL_L;
}
//不产生ACK应答
void IIC_NAck(void)
{
	IIC_SCL_L;
	SDA_OUT();
	IIC_SDA_H;
	delay_us(2);
	IIC_SCL_H;
	delay_us(2);
	IIC_SCL_L;
}
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答
void IIC_Send_Byte(uint8_t txd)
{
	uint8_t t;
	SDA_OUT();
	IIC_SCL_L;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA_H;
		else
			IIC_SDA_L;
		txd<<=1;
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL_H;
		delay_us(2);
		IIC_SCL_L;
		delay_us(2);
    }
}
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK
uint8_t IIC_Read_Byte(uint8_t ack)
{
	uint8_t i,receive=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
    	IIC_SCL_L;
        delay_us(2);
        IIC_SCL_H;
        receive<<=1;
        if(HAL_GPIO_ReadPin(SDA_24C0X_GPIO_Port, SDA_24C0X_Pin))receive++;
		delay_us(1);
    }
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK
    return receive;
}





