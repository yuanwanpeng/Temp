/*
 * dma.c
 *
 *  Created on: 2018��10��30��
 *      Author: YuanWP
 */
#include "dma.h"

extern DMA_HandleTypeDef hdma_usart2_tx;
//DMA1�ĸ�ͨ������
//����Ĵ�����ʽ�ǹ̶���,���Ҫ���ݲ�ͬ��������޸�
//�Ӵ洢��->����ģʽ/8λ���ݿ��/�洢������ģʽ
//chx:DMAͨ��ѡ��,DMA1_Channel1~DMA1_Channel7
void MYDMA_Config(DMA_Channel_TypeDef *chx)
{
	__HAL_RCC_DMA1_CLK_ENABLE();			//DMA1ʱ��ʹ��

    __HAL_LINKDMA(&huart2,hdmatx,hdma_usart2_tx);    		//��DMA��USART1��ϵ����(����DMA)

    //Rx DMA����
    hdma_usart2_tx.Instance=chx;                            		//ͨ��ѡ��
    hdma_usart2_tx.Init.Direction=DMA_MEMORY_TO_PERIPH;             //�洢��������
    hdma_usart2_tx.Init.PeriphInc=DMA_PINC_DISABLE;                 //���������ģʽ
    hdma_usart2_tx.Init.MemInc=DMA_MINC_ENABLE;                     //�洢������ģʽ
    hdma_usart2_tx.Init.PeriphDataAlignment=DMA_PDATAALIGN_BYTE;    //�������ݳ���:8λ
    hdma_usart2_tx.Init.MemDataAlignment=DMA_MDATAALIGN_BYTE;       //�洢�����ݳ���:8λ
    hdma_usart2_tx.Init.Mode=DMA_NORMAL;                            //������ͨģʽ
    hdma_usart2_tx.Init.Priority=DMA_PRIORITY_MEDIUM;               //�е����ȼ�

    HAL_DMA_DeInit(&hdma_usart2_tx);
    HAL_DMA_Init(&hdma_usart2_tx);
}
//����һ��DMA����
//huart:���ھ��
//pData�����������ָ��
//Size:�����������
void MYDMA_USART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
    HAL_DMA_Start(huart->hdmatx, (uint32_t)pData, (uint32_t)&huart->Instance->DR, Size);//����DMA����

    huart->Instance->CR3 |= USART_CR3_DMAT;//ʹ�ܴ���DMA����
}

