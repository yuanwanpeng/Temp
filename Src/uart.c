/*
 * uart.c
 *
 *  Created on: 2018��7��24��
 *      Author: Administrator
 */
#include "uart.h"
#define MAX_RECV_LEN 256

uint8_t aRxBuffer;			//�����жϻ���
uint8_t Uart1_RxBuff[10];		//���ջ���
uint8_t Uart1_Rx_Cnt = 0;		//���ջ������
uint8_t	cAlmStr[] = "�������(����256)\r\n";

uint8_t a2RxBuffer;			//�����жϻ���
uint8_t Uart2_RxBuff[MAX_RECV_LEN];		//���ջ���
uint8_t Uart2_Rx_Cnt = 0;		//���ջ������
/*
 *     ����3����
 */
void Send_To_Uart2_Str(int8_t* str,uint32_t len)
{
	uint8_t i;
	//printf("strlen = %d\r\n",strlen(str));
	for(i = 0; i < len;i++)
	{
		HAL_UART_Transmit(&huart2, (uint8_t*)str+i, 1, 0xff);
	}
	HAL_UART_Receive_IT(&huart2, (uint8_t *)&a2RxBuffer, 1);   //�ٿ��������ж�
}
/********************************************************************************
 *  @brief  HAL_UART_RxCpltCallback  �����жϺ�HAL�������������
* 	@param  ���ھ��
*	 @retval NONE
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(USART1 == huart->Instance)//���Դ���1
	{
		if(Uart1_Rx_Cnt >= (MAX_RECV_LEN+1))  //����ж�
		{
			Uart1_Rx_Cnt = 0;
			memset(Uart1_RxBuff,0x00,sizeof(Uart1_RxBuff));
			HAL_UART_Transmit(&huart1, (uint8_t *)&cAlmStr, sizeof(cAlmStr),0xFFFF);
		}else{
			Uart1_RxBuff[Uart1_Rx_Cnt++] = aRxBuffer;   //��������ת��

			if((Uart1_RxBuff[Uart1_Rx_Cnt-1] == 0x0A)&&(Uart1_RxBuff[Uart1_Rx_Cnt-2] == 0x0D)) //�жϽ���λ
			{
				HAL_UART_Transmit(&huart1, (uint8_t *)&Uart1_RxBuff, Uart1_Rx_Cnt,0xFFFF); //���յ�����Ϣ���ͳ�ȥ
				Uart1_Rx_Cnt = 0;
				memset(Uart1_RxBuff,0x00,sizeof(Uart1_RxBuff)); //�������
			}
		}
		HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1);   //�ٿ��������ж�
	}

	if(USART2 == huart->Instance)//wifiģ�鴮��2
	{
		if(Uart2_Rx_Cnt >= (MAX_RECV_LEN+1))  //����ж�
		{
			Uart2_Rx_Cnt = 0;
			memset(Uart2_RxBuff,0x00,sizeof(Uart2_RxBuff));
			//HAL_UART_Transmit(&huart1, (uint8_t *)&cAlmStr, sizeof(cAlmStr),0xFFFF);//���͸�����һ
		}else{
			Uart2_RxBuff[Uart2_Rx_Cnt++] = a2RxBuffer;   //��������ת��**********�ص�
//			if((Uart2_RxBuff[Uart2_Rx_Cnt-1] == 0x0A)&&(Uart2_RxBuff[Uart2_Rx_Cnt-2] == 0x0D)) //�жϽ���λ
//			{
//				//������һ֡����/r/nΪ��β
//				HAL_UART_Transmit(&huart1, (uint8_t *)&Uart2_RxBuff, Uart2_Rx_Cnt,0xFFFF); //���յ�����Ϣ���ͳ�ȥ
//				Uart2_Rx_Cnt = 0;
//				memset(Uart2_RxBuff,0x00,sizeof(Uart2_RxBuff)); //�������
//			}
		}
		HAL_UART_Receive_IT(&huart2, (uint8_t *)&a2RxBuffer, 1);   //�ٿ��������ж�
	}
}



