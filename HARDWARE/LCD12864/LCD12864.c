/*
 * LCD12864.c
 *
 *  Created on: 2018��7��25��
 *      Author: YuanWP
 */

#include "LCD12864.h"
#include "button.h"
#include "TypeFace.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "relay.h"
#include "task.h"

extern float temp;
extern RTC_HandleTypeDef hrtc;
extern uint8_t G_Echo;
osThreadId Start_LCD12864_HUMI_TaskHandle = NULL;
osThreadId Start_LCD12864_Menu_TaskHandle = NULL;
osThreadId Start_LCD12864_Dispatch_TaskHandle;

volatile New_page_enum Now_page = Humi_Page;

/*
 * void writec(uchar com)
 * д�����
 * */
void WriteCommand(uint8_t CommandByte)
{
	uint8_t i;
	CS_L;
	A0_L;
	//printf("%02x\r\n",CommandByte);
	for(i=0;i<8;i++)
	{
		if(CommandByte&0x80)
		{
			SDA_H;
		}else{
			SDA_L;
		}
		SCL_H;
		CommandByte=CommandByte<<1;
		SCL_L;
		delay_us(1);
	}

	CS_H;
	A0_H;
}
void Write_Data(uint8_t dat)
{
	uint8_t i;
	CS_L;
	A0_H;

	for(i=0;i<8;i++)
	{
		if(dat&0x80)
		{
			SDA_H;
		}else{
			SDA_L;
		}
		SCL_H;
		dat=dat<<1;
		SCL_L;
		delay_us(1);
	}
	CS_H;
	A0_H;
}
void LCD12864_Display(uint8_t dat1,uint8_t dat2)
{
	uint8_t row,col;

   for (row=0xb0; row<0xb8; row++)    //0XB0    0XB8
   {
	  WriteCommand(row);//set page address
      WriteCommand(0x10);//set column address
      WriteCommand(0x00);
      for(col=0;col<128;col++)
      {
		Write_Data(dat1);
        Write_Data(dat2);
      }
   }

 //  osDelay(5);
}

/*
 * 12864��ʾ������ʾ����16*16����
 */
void LCD12864_Put_16_16_Char(uint8_t row_addr,uint8_t column_addr,uint8_t chr,uint8_t Base_Color)
{
	uint8_t row,col,i;
	uint8_t* p_temp = Chinese_Menu_Type+chr*32;
	taskENTER_CRITICAL();		//�����ٽ���
	for(row = row_addr;row >= (row_addr-1);row--)
	{
		WriteCommand(row);
		WriteCommand((column_addr>>4)|0x10);		//Set column address (MSB)
		WriteCommand(column_addr&0x0F);				//Set column address (LSB)
		for(i = 0;i < 2;i++)			//(64/8)
		{
			for(col=0;col<8;col++)
			{
				if(Base_Color == WHITE_BASE){		//�ױ���
					Write_Data(*p_temp++);
				}else if(Base_Color == BLACK_BASE){	//����ڵı���
					Write_Data(~(*p_temp++));
				}
			}
		}
	}
	taskEXIT_CRITICAL();//�˳��ٽ���
}
/*
 * 12864��ʾ������ʾ����8*16����
 */
void LCD12864_Put_8_16_Char(uint8_t row_addr,uint8_t column_addr,uint8_t chr,uint8_t Base_Color)
{
	uint8_t row,col;
	uint8_t* p_temp = ASCIIchardot+(chr-0x20)*16;
	taskENTER_CRITICAL();		//�����ٽ���
	for(row = row_addr;row >= (row_addr-1);row--)
	{
		WriteCommand(row);
		WriteCommand((column_addr>>4)|0x10);		//Set column address (MSB)
		WriteCommand(column_addr&0x0F);				//Set column address (LSB)
		for(col=0;col<8;col++)
		{
			if(Base_Color == WHITE_BASE){		//�ױ���
				Write_Data(*p_temp++);
			}else if(Base_Color == BLACK_BASE){	//����ڵı���
				Write_Data(~(*p_temp++));
			}
		}
	}
	taskEXIT_CRITICAL();//�˳��ٽ���
}
/*
 *
 * ��ʼ��LCD12864
*/
void LCD12864_Init(void)
{
	RS_H;
	osDelay(200);
	RS_L;
	osDelay(400);
	RS_H;
	osDelay(200);

	WriteCommand(0xe3);  // reset signal
	WriteCommand(0xa3);  //(0xa2 1/9 bias,1/65 duty )
	WriteCommand(0xa1);  // ADC select
	WriteCommand(0xc0);  // command output select
	WriteCommand(0x2f);  // power control
	WriteCommand(0x23);  // select resistor ratio Rb/Ra
	WriteCommand(0x81);  // select volume
	WriteCommand(0x27);   // vop
	WriteCommand(0xf8);  // x4
	WriteCommand(0x08);  // x4
	WriteCommand(0xb0);//set page address
	WriteCommand(0x10);//set column address
	WriteCommand(0x00);

	WriteCommand(0xaf);  //display on
}

/*
 * ��ӡ�����24x32
 * */
void LCD12864_Put_Symbol_C(void)
{
	uint8_t row,col,i;
	uint8_t* p_temp = Symbol;
	WriteCommand(0xB1);
	WriteCommand(0x11);
	WriteCommand(0x00);
	for(row = 0xB5;row >= 0xB2;row--)
	{
		WriteCommand(row);
		WriteCommand(0x15);	//Set column address (MSB)
		WriteCommand(0x04);		//Set column address (LSB)
		for(i = 0;i < 2;i++)		//(64/8)
		{
			for(col=0;col<12;col++)
			{
				Write_Data(*p_temp++);
			}
		}
	}
}
/*
 * ��x����ʾʲô
 * */
void LCD12864_Put_HUMI(float temp)
{
	uint8_t row,col,i,place;
	uint8_t num[5];
	uint8_t* p_temp;
	uint16_t int_temp;
	int_temp = (temp*10)/1;
	num[0] = int_temp/100;
	num[1] = int_temp%100/10;
	num[2] = 10;			//10��ʾ��.��
	num[3] = int_temp%10;
	//printf("%d\r\n",int_temp);
	for(place = 0;place < 4;place++)
	{
		p_temp = Symbol_number+64*num[place];
		for(row = 0xB5;row >= 0xB2;row--)
		{
			WriteCommand(row);
			WriteCommand(0x11+place);	//Set column address (MSB)
			WriteCommand(0x00);		//Set column address (LSB)
			for(i = 0;i < 2;i++)		//(64/8)
			{
				for(col=0;col<8;col++)
				{
					Write_Data(*p_temp++);
				}
			}
		}
	}
}
/*
 * �ɹ��ַ�
 */
void LCD12864_Display_Success(void)
{
	if(Now_page != Strategy_Menu_Info_page)
	{
		LCD12864_Put_16_16_Char(0xB3,0x44,0x2B,WHITE_BASE);//����
		LCD12864_Put_16_16_Char(0xB3,0x54,0x2C,WHITE_BASE);//����
	}else{
		LCD12864_Put_16_16_Char(0xB5,0x64,0x2B,WHITE_BASE);//����
		LCD12864_Put_16_16_Char(0xB5,0x74,0x2C,WHITE_BASE);//����
	}
}
/*
 * ɾ���ɹ��ַ�
 */
void LCD12864_Display_Clear_Success(void)
{
	if(Now_page != Strategy_Menu_Info_page)
	{
		LCD12864_Put_16_16_Char(0xB3,0x44,0x2D,WHITE_BASE);//����ɾ��
		LCD12864_Put_16_16_Char(0xB3,0x54,0x2D,WHITE_BASE);//����ɾ��
	}else{
		LCD12864_Put_16_16_Char(0xB5,0x64,0x2D,WHITE_BASE);//����ɾ��
		LCD12864_Put_16_16_Char(0xB5,0x74,0x2D,WHITE_BASE);//����ɾ��
	}
}
/*
 * ��ӡ�������ֵ�12864��ʾ  Sim���ź�״̬
 */
void LCD12864_Put_Signel_Sim(void)
{
	uint8_t row,col,i;
	uint8_t* p_temp = Signal_Strength;
	for(row = 0xB7;row >= 0xB6;row--)
	{
		WriteCommand(row);
		WriteCommand(0x10);		//Set column address (MSB)
		WriteCommand(0x04);				//Set column address (LSB)
		for(i = 0;i < 1;i++)			//(64/8)
		{
			for(col=0;col<8;col++)
			{
				Write_Data(*p_temp++);
			}
		}
	}
}
/*
 * ��ӡ�������ֵ�12864��ʾ wifi�ź�״̬
 */
void LCD12864_Put_Signel_Wifi(void)
{
	uint8_t row,col,i;
	uint8_t* p_temp = Wifi_Signel;
	for(row = 0xB7;row >= 0xB6;row--)
	{
		WriteCommand(row);
		WriteCommand(0x11);		//Set column address (MSB)
		WriteCommand(0x00);				//Set column address (LSB)
		for(i = 0;i < 1;i++)			//(64/8)
		{
			for(col=0;col<8;col++)
			{
				Write_Data(*p_temp++);
			}
		}
	}
}
/*
 * ��ӡ�������ֵ�12864��ʾ���״̬
 * 0--ͣת
 * 1--��ת
 * 2--��ת
 */
void LCD12864_Put_Motor_Situation(uint8_t motor_situation)
{
	uint8_t relay1,relay2;
	if(motor_situation == NULL)
	{
		relay1 = RELAY1_STATE;
		relay2 = RELAY2_STATE;
		if(relay1 == 0){//��ʾ����ת
			motor_situation = FOREWARD;
		}else if(relay2 == 0){
			motor_situation = REVERSAL;
		}else if(relay2==relay1){
			motor_situation = STALLING;
		}
	}
	switch(motor_situation){
	case STALLING:			//ͣת
		//p_temp = Chinese_Menu_Type+(0x1d*32);
		LCD12864_Put_16_16_Char(0xB7,0x60,0x1D,WHITE_BASE);//1D�� ͣ ��
		LCD12864_Put_16_16_Char(0xB7,0x70,0x21,WHITE_BASE);//21�� ת ��
		break;
	case FOREWARD:			//��ת
		LCD12864_Put_16_16_Char(0xB7,0x60,0x1F,WHITE_BASE);//1F�� �� ��
		LCD12864_Put_16_16_Char(0xB7,0x70,0x21,WHITE_BASE);//21�� ת ��
		break;
	case REVERSAL:			//��ת
		LCD12864_Put_16_16_Char(0xB7,0x60,0x20,WHITE_BASE);//20�� �� ��
		LCD12864_Put_16_16_Char(0xB7,0x70,0x21,WHITE_BASE);//21�� ת ��
		break;
	}
}

/*
 * ��ӡ�������ֵ�12864��ʾ
 * �ֶ�
 * ����x
 */
void LCD12864_Put_Str_At_Present_Mode(uint8_t mode_num)
{
	if(mode_num>0)
	{
		LCD12864_Put_16_16_Char(0xB7,0x20,0x00,WHITE_BASE);//����
		LCD12864_Put_16_16_Char(0xB7,0x30,0x01,WHITE_BASE);//����
		LCD12864_Put_8_16_Char(0xB7,0x40,mode_num+0x30,WHITE_BASE);

	}else{
		LCD12864_Put_16_16_Char(0xB7,0x20,0x33,WHITE_BASE);//����
		LCD12864_Put_16_16_Char(0xB7,0x30,0x34,WHITE_BASE);//����
		LCD12864_Put_8_16_Char(0xB7,0x40,0x20,WHITE_BASE); //' '
	}

}
/*
 * ��ӡ�������ֵ�12864��ʾ
 */
void LCD12864_Put_Str_Welcome(void)
{
	uint8_t row,col,i,place;
	uint8_t* p_temp = Welcome_type;
	for(place = 0;place <= 6;place++)
	{
		for(row = 0xB6;row >= 0xB2;row--)
		{
			WriteCommand(row);
			WriteCommand(0x10+place);		//Set column address (MSB)
			WriteCommand(0x08);				//Set column address (LSB)
			for(i = 0;i <2;i++)			//
			{
				for(col=0;col<8;col++)
				{
					Write_Data(*p_temp++);
				}
			}
			//*p_temp++;
		}
	}
}
/*
 * ��ڣ�  9999   T 00:00
 */
void LCD12864_Put_Open_Mouth_And_Time(void)
{
	LCD12864_Put_16_16_Char(0xB1,0x04,0x22,WHITE_BASE);//22�� �� ��
	LCD12864_Put_16_16_Char(0xB1,0x14,0x23,WHITE_BASE);//23�� �� ��
	LCD12864_Put_8_16_Char(0xB1,0x21,':',WHITE_BASE);

	LCD12864_Put_8_16_Char(0xB1,0x50+4,'T',WHITE_BASE);
}
/*
 * ������ʱ��ˢ�� ��ʾСʱ�ͷ���
 */
void LCD12864_Refresh_Time(void)
{
	RTC_TimeTypeDef Time;
	char Hours[3];
	char Minutes[3];

	memset(Hours,'0',sizeof(Hours));
	memset(Minutes,'0',sizeof(Minutes));

	HAL_RTC_GetTime(&hrtc,&Time,RTC_FORMAT_BIN);

	sprintf(Hours,"%02d",(int8_t)Time.Hours);
	sprintf(Minutes,"%02d",(int8_t)Time.Minutes);

	LCD12864_Put_8_16_Char(0xB1,0x58+4,Hours[0],WHITE_BASE);
	LCD12864_Put_8_16_Char(0xB1,0x60+4,Hours[1],WHITE_BASE);
	LCD12864_Put_8_16_Char(0xB1,0x68+4,':',WHITE_BASE);
	LCD12864_Put_8_16_Char(0xB1,0x70+4,Minutes[0],WHITE_BASE);
	LCD12864_Put_8_16_Char(0xB1,0x78+4,Minutes[1],WHITE_BASE);
}
/*
 * ������ˢ�� �г���
 */
void LCD12864_Refresh_Route(void)
{
	char Route[10];

	memset(Route,'0',sizeof(Route));

	sprintf(Route,"%04d",(int8_t)G_Now_Route);
	//printf("Route = %s\r\n",Route);

	LCD12864_Put_8_16_Char(0xB1,0x2a-3,Route[0],WHITE_BASE);
	LCD12864_Put_8_16_Char(0xB1,0x32-3,Route[1],WHITE_BASE);
	LCD12864_Put_8_16_Char(0xB1,0x3a-3,Route[2],WHITE_BASE);
	LCD12864_Put_8_16_Char(0xB1,0x42-3,Route[3],WHITE_BASE);
}
/*
 *��ʾ�¶�(ֻ����ʾ)
 */
void Start_LCD12864_Display_HUMI_Task(void const * argument)
{
	LCD12864_Put_Str_At_Present_Mode(G_New_Mode);
	LCD12864_Put_Signel_Sim();
	LCD12864_Put_Signel_Wifi();
	LCD12864_Put_Motor_Situation(NULL);
	LCD12864_Put_Open_Mouth_And_Time();
	while(1)
	{
		LCD12864_Put_HUMI(temp);
		LCD12864_Put_Symbol_C();
		LCD12864_Refresh_Time();
		LCD12864_Refresh_Route();
		LCD12864_Put_Motor_Situation(NULL);
		Now_page = Humi_Page;
		osDelay(1000);
	}
}



void Send_Notify(uint8_t key)
{
	if(Now_page == Humi_Page)
	{
		if(Start_Relay_TaskHandle != NULL)
		{
			xTaskNotify((TaskHandle_t)Start_Relay_TaskHandle,//��Ϊ�ⲻ�ǲ˵��ڲ������Բ����˵��з���Ϣ
						(uint32_t)key,
						(eNotifyAction)eSetValueWithOverwrite);
		}
	}else if(Now_page == Menu_Page)
	{
		if(Start_LCD12864_Menu_TaskHandle != NULL)
		{
			xTaskNotify((TaskHandle_t)Start_LCD12864_Menu_TaskHandle,
						(uint32_t)key,
						(eNotifyAction)eSetValueWithOverwrite);
		}
	}else if(Now_page == Strategy_Menu)
	{
		if(Start_LCD12864_Set_Strategy_TaskHandle != NULL)
		{
			xTaskNotify((TaskHandle_t)Start_LCD12864_Set_Strategy_TaskHandle,
						(uint32_t)key,
						(eNotifyAction)eSetValueWithOverwrite);
		}
	}else if(Now_page == Route_Reset_page)
	{
		if(Start_LCD12864_Route_Reset_TaskHandle != NULL)
		{
			xTaskNotify((TaskHandle_t)Start_LCD12864_Route_Reset_TaskHandle,
						(uint32_t)key,
						(eNotifyAction)eSetValueWithOverwrite);
		}
	}else if(Now_page == Max_Route_page)
	{
		if(Start_LCD12864_Max_Route_TaskHandle != NULL)
		{
			xTaskNotify((TaskHandle_t)Start_LCD12864_Max_Route_TaskHandle,
						(uint32_t)key,
						(eNotifyAction)eSetValueWithOverwrite);
		}
	}else if(Now_page == HUMI_Compensation_page)
	{
		if(Start_LCD12864_HUMI_Compensation_TaskHandle != NULL)
		{
			xTaskNotify((TaskHandle_t)Start_LCD12864_HUMI_Compensation_TaskHandle,
						(uint32_t)key,
						(eNotifyAction)eSetValueWithOverwrite);
		}
	}else if(Now_page == Delay_Inspection_page)
	{
		if(Start_LCD12864_Delay_Inspection_TaskHandle != NULL)
		{
			xTaskNotify((TaskHandle_t)Start_LCD12864_Delay_Inspection_TaskHandle,
						(uint32_t)key,
						(eNotifyAction)eSetValueWithOverwrite);
		}
	}else if(Now_page == Set_Time_page)
	{
		if(Start_LCD12864_Set_Time_TaskHandle != NULL)
		{
			xTaskNotify((TaskHandle_t)Start_LCD12864_Set_Time_TaskHandle,
						(uint32_t)key,
						(eNotifyAction)eSetValueWithOverwrite);
		}
	}else if(Now_page == Stroking_Cycle_page)
	{
		if(Start_LCD12864_Stroking_Cycle_TaskHandle != NULL)
		{
			xTaskNotify((TaskHandle_t)Start_LCD12864_Stroking_Cycle_TaskHandle,
						(uint32_t)key,
						(eNotifyAction)eSetValueWithOverwrite);
		}
	}else if(Now_page == Strategy_Menu_Info_page)
	{
		if(Start_LCD12864_Set_Strategy_Info_TaskHandle != NULL)
		{
			xTaskNotify((TaskHandle_t)Start_LCD12864_Set_Strategy_Info_TaskHandle,
						(uint32_t)key,
						(eNotifyAction)eSetValueWithOverwrite);
		}
	}
}

/*
 * ҳ����Ⱥ���
 * ֻҪ����Ҳ����ʾ�Ĳ�����
 * */
void Start_LCD12864_Task(void const * argument)
{
	BaseType_t err;

	uint32_t NotifyValue;
	LCD12864_Init();
	LCD12864_Display(0x00,0x00);
	LCD12864_Put_Str_Welcome();
	osDelay(5000);
	LCD12864_Display(0x00,0x00);
	taskENTER_CRITICAL();				//�����ٽ���
	osThreadDef(LCD12864_Display_HUMI_Task, Start_LCD12864_Display_HUMI_Task, osPriorityNormal, 0, 64);//�����¿�ģ��
	Start_LCD12864_HUMI_TaskHandle = osThreadCreate(osThread(LCD12864_Display_HUMI_Task), NULL);
	taskEXIT_CRITICAL();				//�˳��ٽ���
	while(1)
	{
		err = xTaskNotifyWait((uint32_t)0x00,
						(uint32_t)0xffffffff,
						(uint32_t*)&NotifyValue,
						(TickType_t)portMAX_DELAY);
		G_Echo = 0;
		if(err==pdTRUE)
		{
			if(((uint8_t)NotifyValue)==K_1_num)		//���ܰ���
			{
				if(Now_page == Humi_Page)
				{
					vTaskSuspend(Start_LCD12864_HUMI_TaskHandle);		//����lcd12864��ʾ�¶ȵĽ���
					osThreadDef(LCD12864_Display_Menu_Task, Start_LCD12864_Display_Menu_Task, osPriorityNormal, 0, 64);//�����˵�����
					Start_LCD12864_Menu_TaskHandle = osThreadCreate(osThread(LCD12864_Display_Menu_Task), NULL);
				}else{
					Send_Notify(K_1_num);
				}
			}
			if(((uint8_t)NotifyValue)==K_2_num)		//���ϰ���
			{
				Send_Notify(K_2_num);
			}
			if(((uint8_t)NotifyValue)==K_3_num)		//���°���
			{
				Send_Notify(K_3_num);
			}
			if(((uint8_t)NotifyValue)==K_4_num)		//ȡ������
			{
				Send_Notify(K_4_num);
			}
			if(((uint8_t)NotifyValue)==K_2_num_long)	//���ϰ�������
			{
				Send_Notify(K_2_num_long);
			}
			if(((uint8_t)NotifyValue)==K_3_num_long)	//���°�������
			{
				Send_Notify(K_3_num_long);
			}
			if(((uint8_t)NotifyValue)==K_4_num_long)	//ȡ����������
			{
				Send_Notify(K_4_num_long);
			}
		}
	}
}


