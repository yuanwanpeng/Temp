/*
 * uart.c
 *
 *  Created on: 2018年7月24日
 *      Author: Administrator
 */
#include "uart.h"
#define MAX_RECV_LEN 256

uint8_t aRxBuffer;			//接收中断缓冲
uint8_t Uart1_RxBuff[10];		//接收缓冲
uint8_t Uart1_Rx_Cnt = 0;		//接收缓冲计数
uint8_t	cAlmStr[] = "数据溢出(大于256)\r\n";

uint8_t a2RxBuffer;			//接收中断缓冲
uint8_t Uart2_RxBuff[MAX_RECV_LEN];		//接收缓冲
uint8_t Uart2_Rx_Cnt = 0;		//接收缓冲计数
/*
 *     串口3发送
 */
void Send_To_Uart2_Str(int8_t* str,uint32_t len)
{
	uint8_t i;
	//printf("strlen = %d\r\n",strlen(str));
	for(i = 0; i < len;i++)
	{
		HAL_UART_Transmit(&huart2, (uint8_t*)str+i, 1, 0xff);
	}
	HAL_UART_Receive_IT(&huart2, (uint8_t *)&a2RxBuffer, 1);   //再开启接收中断
}
/********************************************************************************
 *  @brief  HAL_UART_RxCpltCallback  进入中断后HAL库会调用这个函数
* 	@param  串口句柄
*	 @retval NONE
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(USART1 == huart->Instance)//调试串口1
	{
		if(Uart1_Rx_Cnt >= (MAX_RECV_LEN+1))  //溢出判断
		{
			Uart1_Rx_Cnt = 0;
			memset(Uart1_RxBuff,0x00,sizeof(Uart1_RxBuff));
			HAL_UART_Transmit(&huart1, (uint8_t *)&cAlmStr, sizeof(cAlmStr),0xFFFF);
		}else{
			Uart1_RxBuff[Uart1_Rx_Cnt++] = aRxBuffer;   //接收数据转存

			if((Uart1_RxBuff[Uart1_Rx_Cnt-1] == 0x0A)&&(Uart1_RxBuff[Uart1_Rx_Cnt-2] == 0x0D)) //判断结束位
			{
				HAL_UART_Transmit(&huart1, (uint8_t *)&Uart1_RxBuff, Uart1_Rx_Cnt,0xFFFF); //将收到的信息发送出去
				Uart1_Rx_Cnt = 0;
				memset(Uart1_RxBuff,0x00,sizeof(Uart1_RxBuff)); //清空数组
			}
		}
		HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1);   //再开启接收中断
	}

	if(USART2 == huart->Instance)//wifi模块串口2
	{
		if(Uart2_Rx_Cnt >= (MAX_RECV_LEN+1))  //溢出判断
		{
			Uart2_Rx_Cnt = 0;
			memset(Uart2_RxBuff,0x00,sizeof(Uart2_RxBuff));
			//HAL_UART_Transmit(&huart1, (uint8_t *)&cAlmStr, sizeof(cAlmStr),0xFFFF);//发送给串口一
		}else{
			Uart2_RxBuff[Uart2_Rx_Cnt++] = a2RxBuffer;   //接收数据转存**********重点
//			if((Uart2_RxBuff[Uart2_Rx_Cnt-1] == 0x0A)&&(Uart2_RxBuff[Uart2_Rx_Cnt-2] == 0x0D)) //判断结束位
//			{
//				//接收完一帧数据/r/n为结尾
//				HAL_UART_Transmit(&huart1, (uint8_t *)&Uart2_RxBuff, Uart2_Rx_Cnt,0xFFFF); //将收到的信息发送出去
//				Uart2_Rx_Cnt = 0;
//				memset(Uart2_RxBuff,0x00,sizeof(Uart2_RxBuff)); //清空数组
//			}
		}
		HAL_UART_Receive_IT(&huart2, (uint8_t *)&a2RxBuffer, 1);   //再开启接收中断
	}
}



