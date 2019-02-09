/*
 * HTTP.c
 *
 *  Created on: 2018��11��19��
 *      Author: YuanWP
 */
#include "HTTP_CODE.h"
/**
  * @brief   ��HTTP POST����
  * @param   pkt   ���Ļ���ָ��
  * @param   key   API_KEY������Main.c�ļ��У���Ҫ�����Լ����豸�޸�
  *	@param 	 devid �豸ID��������main.c�ļ��У���Ҫ�����Լ����豸�޸�
  *	@param 	 dsid  ������ID
  *	@param 	 val   �ַ�����ʽ�����ݵ��ֵ
  * @retval  �������ĳ���
  */
uint32_t HTTP_PostPkt(int8_t *pkt, int8_t *key, int8_t *devid, int8_t *dsid, int8_t *val)
{
    int8_t dataBuf[100] = {0};
    int8_t lenBuf[10] = {0};
    *pkt = 0;

    sprintf((char*)dataBuf, ",;%s,%s", dsid, val);     //���÷ָ��ַ�����ʽ:type = 5
    sprintf((char*)lenBuf, "%d", strlen((const char*)dataBuf));

    strcat((char*)pkt, "POST /devices/");
    strcat((char*)pkt, (const char*)devid);
    strcat((char*)pkt, "/datapoints?type=5 HTTP/1.1\r\n");

    strcat((char*)pkt, "api-key:");
    strcat((char*)pkt, (const char*)key);
    strcat((char*)pkt, "\r\n");

    strcat((char*)pkt, "Host:api.heclouds.com\r\n");

    strcat((char*)pkt, "Content-Length:");
    strcat((char*)pkt, (const char*)lenBuf);
    strcat((char*)pkt, "\r\n\r\n");

    strcat((char*)pkt, (const char*)dataBuf);

    return strlen((char*)pkt);
}
