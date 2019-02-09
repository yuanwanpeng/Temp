/*
 * Strategy.c
 *
 *  Created on: 2018年11月28日
 *      Author: YuanWP
 */
#include "Strategy.h"
#include "LCD12864_Display_Menu_Set_Strategy.h"
#include "relay.h"
#include "LCD12864.h"
#define	INIT_HOURS		23	//默认的时间
#define	INIT_MINUTES	59
#define	INIT_SECONDS	59
#define INIT_TEMP_H		25	//高温度
#define INIT_TEMP_L		20	//低温度
#define INIT_ROUTE		0	//默认行程
#define	ROUTE_NUM		10

#define NO_CHECK_HOURS	4		//不检测的时间段
#define NO_CHECK_MINUTES	00
#define NO_CHECK_SECONDS	00
extern float temp;

/*
 * 初始化内部策略信息
 */
void Init_Strategy(uint8_t num)
{
	uint8_t i;
	for(i = num;i < 8;i++)
	{
		S_Strategy[i].Strategy_Num = (i+1);		// 初始化缓存任务数据
		S_Strategy[i].Time.Hours = INIT_HOURS;
		S_Strategy[i].Time.Minutes = INIT_MINUTES;
		S_Strategy[i].Time.Seconds = INIT_SECONDS;
		S_Strategy[i].Strategy_State = Strategy_Close;
		S_Strategy[i].Temp_h = INIT_TEMP_H;
		S_Strategy[i].Temp_l = INIT_TEMP_L;
		S_Strategy[i].Route = INIT_ROUTE;
		S_Strategy[i].Strategy_Type = Strategy_Type_Route;//默认风口模式风口
		if(i == 0)
		{
			S_Strategy[i].Strategy_State = Strategy_Open;
			S_Strategy[i].Time.Hours = NO_CHECK_HOURS;	//不许设置的时间段重点
			S_Strategy[i].Time.Minutes = NO_CHECK_MINUTES;
			S_Strategy[i].Time.Seconds = NO_CHECK_SECONDS;
		}
		AT24CXX_Write(i*0x10,((uint8_t*)S_Strategy)+(sizeof(S_Strategy[i])*i),sizeof(S_Strategy[i]));	//写入策略
	}
	for(i = 0;i < 8;i++)
	{
		AT24CXX_Read(i*0x10,((uint8_t*)G_Strategy)+(sizeof(G_Strategy[i])*i),sizeof(G_Strategy[i]));	//读取策略
		//printf("r %d,Hours %d,Minutes %d\r\n",i,G_Strategy[i].Time.Hours,G_Strategy[i].Time.Minutes);
	}
	printf("write all Strategy success%d!!\r\n",sizeof(G_Strategy[i]));
	return;
}
/*
 * 开始检测策略任务
 */
void Start_Strategy_Task(void const * argument)
{
	RTC_TimeTypeDef Time;
	uint8_t i,Old_Strategy = 0,Mark = 0,Strategy_mode = 0;
	uint8_t relay1,relay2;
	uint16_t Min_Time,NEXT_Min_Time,Delay_Time,NEW_Route;
	osDelay(6000);
	while(1)
	{
		if(G_New_Mode != 0)//0是手动模式
		{
			HAL_RTC_GetTime(&hrtc,&Time,RTC_FORMAT_BIN);//获取当前时间
			for(i = 0 ;i < 8;i++)
			{
				if(G_Strategy[i].Strategy_State == Strategy_Open)//查看当前策略是否开启
				{
					Min_Time = G_Strategy[i].Time.Hours * 60 + G_Strategy[i].Time.Minutes;//小时换算成分钟加上分钟
					NEXT_Min_Time = G_Strategy[i+1].Time.Hours * 60 + G_Strategy[i+1].Time.Minutes;//下一个的小时换算成分钟加上分钟
					if(((Time.Hours*60+Time.Minutes) >= Min_Time)&&((Time.Hours*60+Time.Minutes) < NEXT_Min_Time))//策略的时间大于等于当前时间
					{	//当前时间要大于等于            策略时间       当前时间             小于等于  下一个的时间
						//printf("G_New_Mode = %d\r\n",G_New_Mode);
						G_New_Mode = i+1;//判断策略开启，并且时间已经判断相同时间内  设定执行策略
						if(Old_Strategy != G_New_Mode)
						{
							if(Now_page == Humi_Page)
							{
								LCD12864_Put_Str_At_Present_Mode(G_New_Mode);	//lcd显示策略号
							}
							Old_Strategy = G_New_Mode;
						}
					}
				}
			}
			/*根据Now_Strategy_num来执行策略*/
			if(G_Strategy[G_New_Mode-1].Strategy_Type == Strategy_Type_Route)	//当前策略是 行程类型
			{
				if(G_Now_Route > G_Strategy[G_New_Mode-1].Route)		//当前行程大于设定行程
				{
					Motor_Reverses();
				}else if(G_Now_Route < G_Strategy[G_New_Mode-1].Route)	//当前行程小于设定行程
				{
					Motor_Forward();
				}else if(G_Now_Route == G_Strategy[G_New_Mode-1].Route)	//行程相等
				{
					Motor_Stop();
				}
			}else if(G_Strategy[G_New_Mode-1].Strategy_Type == Strategy_Type_Temp)//当前策略是温度恒温类型
			{
				if(Mark == 0)
				{
					Delay_Time = (Time.Hours*60+Time.Minutes);			//记录当前时间
					Mark = 1;
				}
				if((Time.Hours*60+Time.Minutes) >= (Delay_Time+G_Delay_Inspection))//到时间了执行策略
				{
					relay1 = RELAY1_STATE;
					relay2 = RELAY2_STATE;
					if((relay1 == 1)&&(relay2 == 1))//电机没有转动的时候
					{
						//当前行程小于最大行程，大于0
						if((temp > G_Strategy[G_New_Mode-1].Temp_h)&&(G_Now_Route<G_Max_Route))//检测当前温度大于最高温度
						{
							NEW_Route = G_Now_Route;
							Strategy_mode = 1;	//1为正转模式10个点  要做成宏定义
							Motor_Forward();	//正转开风口10个点
						}else if((temp < G_Strategy[G_New_Mode-1].Temp_l)&&(G_Now_Route>0)){
							NEW_Route = G_Now_Route;
							Strategy_mode = 2;	//2为反转模式10个点
			 				Motor_Reverses();	//反转关风口10个点
						}
					}
					Delay_Time = (Time.Hours*60+Time.Minutes);//因为将时间往上加
				}
				switch(Strategy_mode){
					case 1://1表示正转开风口10圈
						Delay_Time = (Time.Hours*60+Time.Minutes);	//因为转动时候不计算时间所以将时间往上加
						if(G_Now_Route >= (NEW_Route+ROUTE_NUM)){
							Mark = 0;
							Strategy_mode = 0;
							Motor_Stop();		//停转
						}
						break;
					case 2:
						Delay_Time = (Time.Hours*60+Time.Minutes);	//因为转动时候不计算时间所以将时间往上加
						if(G_Now_Route <= (NEW_Route-ROUTE_NUM)){
							Mark = 0;
							Strategy_mode = 0;
							Motor_Stop();		//停转
						}
						break;
				}
			}
			osDelay(200);
		}else{
			/*
			 * 手动情况(待定)
			 * */
			osDelay(1000);
		}
	}
}

