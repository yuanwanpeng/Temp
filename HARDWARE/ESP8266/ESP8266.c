/*
 * ESP8266.c
 *
 *  Created on: 2018��9��5��
 *      Author: YuanWP
 */
#include "ESP8266.h"
#include <string.h>
#include "edpkit.h"
#define API_KEY     "SVyUr0x98IjWdz6K=GTQtyAvWqM="		//��Ҫ����Ϊ�û��Լ��Ĳ���
#define DEV_ID      "504820915"							//��Ҫ����Ϊ�û��Լ��Ĳ���


extern uint8_t aRxBuffer;			//�����жϻ���
extern uint8_t Uart1_RxBuff;		//���ջ���
extern uint8_t Uart1_Rx_Cnt;		//���ջ������
extern uint8_t Uart2_RxBuff[];		//���ջ���
extern uint8_t Uart2_Rx_Cnt;		//���ջ������
extern uint8_t	cAlmStr[];
extern float temp;
osThreadId Start_ESP8266_TaskHandle;
EdpPacket* send_pkg;
char send_buf[MAX_SEND_BUF_LEN];
void ConfigAirKiss(void)
{
	SendCmd(SET_AT_CWMODE_1,"OK",1000);
	SendCmd(SET_AT_CWSTARTSMART,"OK",1000);

	while(1)
	{
		if((NULL != strstr((const char *)Uart2_RxBuff, "smartconfig connected wifi")))
		{
			break;
		}else{
			osDelay(1000);
		}
	}

}

/**
  * @brief  ����һ��ATָ��
**/
void SendCmd(int8_t* cmd, int8_t* result, uint16_t timeOut)
{
    while(1)
    {
		memset(Uart2_RxBuff,'\0',strlen((const char *)Uart2_RxBuff)); //�������
        Uart2_Rx_Cnt=0;
        Send_To_Uart2_Str(cmd,strlen((const char *)cmd));
        osDelay(timeOut);
        printf("%s",Uart2_RxBuff);
        if((NULL != strstr((const char *)Uart2_RxBuff, (const char *)result)))	//�ж��Ƿ���Ԥ�ڵĽ��
        {
            break;
        }else if((NULL != strstr((const char *)Uart2_RxBuff, "no ip")))	//�ж���û��ip
        {
        	//����airkissģʽ
        	ConfigAirKiss();
        	osDelay(100);
        }else{
        	osDelay(1000);
        }
    }
}

/**
  * @brief  ��ƽ̨�����豸����
**/
void ESP8266_DevLink(const char* devid, const char* auth_key, uint32_t timeOut)
{
	uint32_t count=0;
	memset(Uart2_RxBuff,'\0',strlen((const char *)Uart2_RxBuff)); //�������
	Uart2_Rx_Cnt=0;
	printf("%s\r\n","[ESP8266_DevLink]ENTER device link...");

	Send_To_Uart2_Str(SET_AT_CIPSEND,strlen(SET_AT_CIPSEND));

	for(count=0;count<timeOut;count++)
	{
		osDelay(100);
		if((NULL != strstr((const char *)Uart2_RxBuff,">")))
		{
			break;
		}
	}
	send_pkg = PacketConnect1(devid,auth_key);
	osDelay(200);
	//usart2_write(USART2,send_pkg->_data,send_pkg->_write_pos);  //�����豸������������
	Send_To_Uart2_Str((int8_t*)send_pkg->_data,send_pkg->_write_pos);
	osDelay(500);
	DeleteBuffer(&send_pkg);
	osDelay(200);
	Send_To_Uart2_Str("+++",strlen("+++"));  //��ESP8266����+++����͸����ʹESP8266����ָ��ģʽ
	osDelay(50);
	printf("%s\r\n","[ESP8266_DevLink]EXIT device link...");
}


/**
  * @brief  ESP8266��ʼ��
**/
void ESP8266_Init(void)
{
	printf("[AT]\r\n");
	SendCmd(AT,"OK",500);

	printf("[SET_AT_CWMODE_1]\r\n");
	SendCmd(SET_AT_CWMODE_1,"OK",500);

//	SendCmd(AT_RST,"ready",3000);
	
	osDelay(3000);
	printf("[GET_AT_CIFSR]\r\n");
	SendCmd(GET_AT_CIFSR,"OK",3000);

	//SendCmd(SET_AT_CWJAP_DEF,"OK",2200);		//����wifi�˺�����
	printf("[SET_AT_CIPSTART]\r\n");
	SendCmd(SET_AT_CIPSTART,"OK",2200);//͸��ģʽ
	
	printf("[SET_AT_CIPMODE_1]\r\n");
	SendCmd(SET_AT_CIPMODE_1,"OK",1000);//͸��ģʽ
	
	printf("ESP8266_Init success\r\n");
}
/**
  * @brief  ���ESP8266����״̬
**/
int16_t ESP8266_CheckStatus(int16_t timeOut)
{
	int32_t res=0;
	int32_t count=0;

	memset((char*)Uart2_RxBuff,0,strlen((const char*)Uart2_RxBuff));
	Uart2_Rx_Cnt=0;

//	printf("%s\r\n","[ESP8266_CheckStatus]ENTER check status...");
	Send_To_Uart2_Str(GET_AT_CIPSTATUS,strlen(GET_AT_CIPSTATUS));
	for(count=0;count<timeOut;count++)
	{
		osDelay(100);
		if((NULL != strstr((const char *)Uart2_RxBuff,"STATUS:4")))  //ʧȥ����
		{
			res=-4;
			break;
		}
		else if((NULL != strstr((const char *)Uart2_RxBuff,"STATUS:3")))  //��������
		{
			res=0;
			break;
		}
		else if((NULL != strstr((const char *)Uart2_RxBuff,"STATUS:2")))  //���IP
		{
			res=-2;
			break;
		}
		else if((NULL != strstr((const char *)Uart2_RxBuff,"STATUS:5")))  //�������
		{
			res=-5;
			break;
		}
		else if((NULL != strstr((const char *)Uart2_RxBuff,"ERROR")))
		{
			res=-1;
			break;
		}
		else
		{
			;
		}
	}
//	printf("%s\r\n","[ESP8266_CheckStatus]EXIT check status...");
	return res;
}
/**
  * @brief  ����LED��ǰ״̬���ϴ����ݣ��ָ��ַ�����ʽ
**/
void GetSendBuf(void)
{
	char text[25] = {0};
	uint8_t num[5];
	uint16_t int_temp;
	int_temp = (temp*10)/1;
	memset(num,'\0',sizeof(num));
	text[0] = (int_temp/100)+0x30;
	text[1] = (int_temp%100/10)+0x30;
	text[2] = '.';					//��.��
	text[3] = (int_temp%10)+0x30;
	text[4] = 0;

	memset(send_buf,0,MAX_SEND_BUF_LEN);

	strcat(send_buf, ",;");
	strcat(send_buf, "temp,");
	strcat(send_buf, text);
	strcat(send_buf, ";");
//
//	strcat(send_buf, "green_statu,");
//	sprintf(text,"%d",0);
//	strcat(send_buf, text);
//	strcat(send_buf, ";");
}
/**
  * @brief  ��ƽ̨�ϴ�LED��ǰ״̬����
**/
void ESP8266_SendDat(void)
{
	int32_t count=0;

	memset(Uart2_RxBuff,0,strlen((const char*)Uart2_RxBuff));
	Uart2_Rx_Cnt=0;
	//printf("%s\r\n","[ESP8266_SendDat]ENTER Senddata...");
	Send_To_Uart2_Str(SET_AT_CIPSEND,strlen(SET_AT_CIPSEND));  //��ESP8266��������͸��ָ��
	for(count=0;count<40;count++)
	{
		osDelay(100);
		if((NULL != strstr((const char *)Uart2_RxBuff,">")))
		{
				break;
		}
	}
	GetSendBuf();
	send_pkg = PacketSavedataSimpleString(DEV_ID,send_buf);
	Send_To_Uart2_Str((int8_t*)send_pkg->_data,send_pkg->_write_pos);	//��ƽ̨�ϴ����ݵ�
	DeleteBuffer(&send_pkg);
	osDelay(500);

	Send_To_Uart2_Str("+++",3);  //��ESP8266����+++����͸����ʹESP8266����ָ��ģʽ
	osDelay(200);
	//printf("%s\r\n","[ESP8266_SendDat]EXIT Senddata...");
}


/*
 *
 */
void Start_ESP8266_Task(void const * argument)
{
	osDelay(1000);
	ESP8266_Init();    //ESP8266��ʼ��
	ESP8266_DevLink(DEV_ID,API_KEY,20);    //��ƽ̨�����豸����
	while(1)
	{
		if(!(ESP8266_CheckStatus(30)))    //���ESP8266ģ������״̬
		{
			ESP8266_SendDat();     //��ƽ̨��������
		}
		else
		{
			break;
		}
		osDelay(8000);
	}
}
/*
 * ��ѯ�豸ip
 */
void AT_CIFSR(void)
{
	Send_To_Uart2_Str(GET_AT_CIFSR,strlen(GET_AT_CIFSR));
}
/*
 * ����TCP
 */
void AT_CIPSTART_COM(void)
{
	printf("%s",SET_AT_CIPSTART);
	
	Send_To_Uart2_Str(SET_AT_CIPSTART,strlen(SET_AT_CIPSTART));
}


/*
 * ���뱻̽��ģʽ
 */
void AT_CWSTARTSMART(void)
{
	Send_To_Uart2_Str(SET_AT_CWSTARTSMART,strlen(SET_AT_CWSTARTSMART));
}
//void Start_ESP8266_Task(void const * argument)
//{
//	json_t *root;
//	char *out;
//
//	while(1)
//	{
//		osDelay(1000);
//		/* Build an empty JSON object */
//		root = json_pack("{}");
//
//		out = json_dumps(root, JSON_ENCODE_ANY);
//		printf("out:%s\r\n", out);
//		free(root);
//		free(out);
//
//		/* Build the JSON object {"foo": 42, "bar": 7} */
//		root = json_pack("{sisi}", "foo", 42, "bar", 7);
//
//		out = json_dumps(root, JSON_ENCODE_ANY);
//		printf("out:%s\r\n", out);
//		free(root);
//		free(out);
//
//		/* Like above, ':', ',' and whitespace are ignored */
//		root = json_pack("{s:i, s:i}", "foo", 42, "bar", 7);
//		out = json_dumps(root, JSON_ENCODE_ANY);
//		printf("out:%s\r\n", out);
//		free(root);
//		free(out);
//
//		/* Build the JSON array [[1, 2], {"cool": true}] */
//		root = json_pack("[[i,i],{s:b}]", 1, 2, "cool", 1);
//		out = json_dumps(root, JSON_ENCODE_ANY); printf("out:%s\r\n", out);
//		free(root);
//		free(out);
//
//		/* Build a string from a non-null terminated buffer */
//		char buffer[4] = {'t', 'e', 's', 't'};
//		root = json_pack("[s#]", buffer, 4);
//		out = json_dumps(root, JSON_ENCODE_ANY);
//		printf("out:%s\r\n", out);
//		free(root);
//		free(out);
//
//		while(1)
//		{
//			osDelay(1000);
//		}
//	}
//}
//
