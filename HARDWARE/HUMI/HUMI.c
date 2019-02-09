/*
 * HUMI.c
 *
 *  Created on: 2018年8月14日
 *      Author: YuanWP
 */
#include "HUMI.h"
#include "main.h"
#include "cmsis_os.h"
#include "stm32f1xx_hal.h"
#include "LCD12864.h"
#include <math.h>
extern ADC_HandleTypeDef hadc1;
extern osThreadId Start_LCD12864_HUMI_TaskHandle;
float Compensation = 10.2;
const float Rp=10000.0;             //10K
const float T2 = (273.15+25.0); //T2
const float Bx = 3950.0;              //B
const float Ka = 273.15;
float temp;
float comp = 0.5;

void Init_Humi_Comp(void)
{
	int8_t S_comp;
	AT24CXX_Read(HUMI_COMP,(uint8_t*)&S_comp,sizeof(S_comp));
//	printf("S_comp = %d\r\n",S_comp);
	if((S_comp<-50)||(S_comp>50))
	{
//		printf("reinit comp\r\n");
		S_comp = 5;			//初始化为0.5补偿
		AT24CXX_Write(HUMI_COMP,(uint8_t*)&S_comp,sizeof(S_comp));
		AT24CXX_Read(HUMI_COMP,(uint8_t*)&S_comp,sizeof(S_comp));
	}

	comp = ((float)S_comp)/10;
}



float Get_TempResistor(void)
{
	float Rt;
	int32_t value;
	float voltage=1.55;
	HAL_ADC_Start(&hadc1);
	value = HAL_ADC_GetValue(&hadc1);
	voltage = value*(3.3/4096);
	Rt = voltage*Rp/(3.29-voltage);
	//printf("voltage = %2.4f,Rt = %5.4f\r\n",voltage,Rt);

	return Rt;
}

void Start_HUMI_Task(void const * argument)
{
	float Rt;
	HAL_ADC_Start(&hadc1);

	LCD12864_Display(0x00,0x00);
	osDelay(5000);
	while(1)
	{
		Rt = Get_TempResistor();   //获得电阻值
		temp = Rt/Rp;
		temp = log(temp); //ln(Rt/Rp)
		temp /= Bx; //ln(Rt/Rp)/B
		temp+=(1/T2); //ln(Rt/Rp)/B+（1/T2）
		temp = 1/(temp);
		temp-=Ka;
		temp+=comp; //加0.5误差矫正
//		temp = 1/(log(Rt/Rp)/Bx + (1/T2));
//		temp = (temp - Ka + 0.5)*10;
		//printf("temp = %2.4f\r\n",temp);
		osDelay(1000);
//		xTaskNotify((TaskHandle_t)Start_LCD12864_HUMI_TaskHandle,
//					(uint32_t)temp,
//					(eNotifyAction)eSetValueWithOverwrite);
//		LCD12864_Put_HUMI(temp);
//		LCD12864_Put_Symbol_C();
	}
}



