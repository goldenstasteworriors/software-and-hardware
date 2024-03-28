#include "grip.h"
#include "tim.h"
#include "motor_pid.h"
#include "math.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#define pi 3.1415926
float servoAngle[5] = {32, -112, -10, 0, 0};
float servoRefAngle[4] = {0, 7, -74, -23};
extern QueueHandle_t	myQueue01Handle;
MecArmAttiSturcture  tx;	
void rm_servo(double angle)
{
		float arr ;
		if(servoRefAngle[3] < angle)
		{
			for(; servoRefAngle[3] < angle; servoRefAngle[3]++)
			{
				arr = 0.3*servoRefAngle[3] + 365;
				TIM8->CCR1 = arr;
		
				vTaskDelay(20);
			}
		}
		if(servoRefAngle[3] >= angle)
		{
			for(; servoRefAngle[3] >= angle; servoRefAngle[3]--)
			{
				arr = 0.3*servoRefAngle[3] + 365;
				TIM8->CCR1 = arr;
		
				vTaskDelay(20);
			}
		}
		

}
//void servo1(float angle)
//{
//		//大疆板子对应APB1外设，时钟频率对应36Mhz
//		//三线舵机占空比为2.5%到12.5%，最小值为4199*2.5%=105 最大值为4199*12.5%=524
//		//对应角度 ccr = 0.5*angle + 179
//		float arr ;
//		if(servoRefAngle[0] < angle)
//		{
//			for(; servoRefAngle[0] < angle; servoRefAngle[0]++)
//			{
//				arr = 2.3*servoRefAngle[0] + 315;
//				TIM2->CCR1 = arr;			
//				vTaskDelay(10);
//			}
//		}
//		if(servoRefAngle[0] >= angle)
//		{
//			for(; servoRefAngle[0] >= angle; servoRefAngle[0]--)
//			{
//				arr = 2.3*servoRefAngle[0] + 315;
//				TIM2->CCR1 = arr;
//				vTaskDelay(10);
//			}
//		}
////		arr = 2.3*angle + 315;
////		TIM2->CCR1 = arr;
//		//-90~90

//}
//void servo2(float angle)
//{
//		//大疆板子对应APB1外设，时钟频率对应36Mhz
//		//三线舵机占空比为2.5%到12.5%，最小值为3599*2.5%=89.975 最大值为3599*12.5%=449.875
//		//对应角度 ccr = 2.3*angle + 524
//		float arr ;
//		if(servoRefAngle[1] < angle)
//		{
//			for(; servoRefAngle[1] < angle; servoRefAngle[1]++)
//			{
//				arr = 2.3*servoRefAngle[1] + 524;
//				TIM2->CCR2 = arr;
//		
//				vTaskDelay(10);
//			}
//		}
//		if(servoRefAngle[1] >= angle)
//		{
//			for(; servoRefAngle[1] >= angle; servoRefAngle[1]--)
//			{
//				arr = 2.3*servoRefAngle[1] + 524;
//				TIM2->CCR2 = arr;
//		
//				vTaskDelay(10);
//			}
//		}
////		arr = 2.3*angle + 524;
////		TIM2->CCR2 = arr;
//		//-180到0
//}
//void servo3(float angle)
//{
//		//大疆板子对应APB1外设，时钟频率对应36Mhz
//		//三线舵机占空比为2.5%到12.5%，最小值为4199*2.5%=105 最大值为4199*12.5%=524
//		//对应角度 ccr = 2.3*angle + 315
//		float arr ;
//		if(servoRefAngle[2] < angle)
//		{
//			for(; servoRefAngle[2] < angle; servoRefAngle[2]++)
//			{
//				arr = 2.3*servoRefAngle[2] + 315;
//				TIM2->CCR3 = arr;
//		
//				vTaskDelay(10);
//			}
//		}
//		if(servoRefAngle[2] >= angle)
//		{
//			for(; servoRefAngle[2] >= angle; servoRefAngle[2]--)
//			{
//				arr = 2.3*servoRefAngle[2] + 315;
//				TIM2->CCR3 = arr;
//		
//				vTaskDelay(10);
//			}
//		}
////			arr = 2.3*angle + 315;
////			TIM2->CCR3 = arr;
//		//-90~90
//}
void clip(double angle)
{
		//大疆板子对应APB1外设，时钟频率对应36Mhz
		//三线舵机占空比为2.5%到12.5%，最小值为3599*2.5%=89.975 最大值为3599*12.5%=449.875
		//对应角度 ccr = 0.5*angle + 179
		float arr ;
		arr = 2.3*angle + 315;
		TIM2->CCR4 = arr;
		//HAL_Delay(100);

}


void init_pos()
{
	for(int i = 0; i < 4; i++)
	{
		servoRefAngle[i] = servoAngle[i];
	}
	tx.mode = 0;
	tx.pointX = 0;
	tx.pointY = 0.18;
	tx.pointZ = 0.27;
	tx.clip_angle = -26;
	tx.time_delta[0] = 0;
	tx.time_delta[1] = 0;
	tx.time_delta[2] = 0;
	tx.time_delta[3] = 0;
	xQueueSendToBack(myQueue01Handle, &tx, 0);
	
}
void move_get()
{
	tx.mode = 0;
	tx.pointX = 0;
	tx.pointY = 0.35;
	tx.pointZ = 0.08;
	tx.clip_angle = -26;
	tx.time_delta[0] = 0;
	tx.time_delta[1] = 0;
	tx.time_delta[2] = 0;
	tx.time_delta[3] = 0;
	xQueueSendToBack(myQueue01Handle, &tx, 0);
	
}
void move_get2()
{
	tx.mode = 0;
	tx.pointX = 0;
	tx.pointY = 0.35;
	tx.pointZ = 0.08;
	tx.clip_angle = -10;
	tx.time_delta[0] = 0;
	tx.time_delta[1] = 0;
	tx.time_delta[2] = 0;
	tx.time_delta[3] = 0;
	xQueueSendToBack(myQueue01Handle, &tx, 0);
	

}
void up()
{
		tx.mode = 0;
		tx.pointX = 0;
		tx.pointY = 0.15;
		tx.pointZ = 0.13;
		tx.clip_angle = -10;
		tx.time_delta[0] = 0;
		tx.time_delta[1] = 0;
		tx.time_delta[2] = 0;
		tx.time_delta[3] = 0;
		xQueueSendToBack(myQueue01Handle, &tx, 0);
		

}
void move_turn()
{
		tx.mode = 0;
		tx.pointX = 0.3;
		tx.pointY = -0.1;
		tx.pointZ = 0.15;
		tx.clip_angle = -10;
		tx.time_delta[0] = 0;
		tx.time_delta[1] = 0;
		tx.time_delta[2] = 0;
		tx.time_delta[3] = 0;
		xQueueSendToBack(myQueue01Handle, &tx, 0);
		
}
void move_put()
{
		tx.mode = 1;
		tx.pointX = 0.3;
		tx.pointY = 0.05;
		tx.pointZ = 0.05;
		tx.clip_angle = -26;
		tx.time_delta[0] = 0;
		tx.time_delta[1] = 0;
		tx.time_delta[2] = 0;
		tx.time_delta[3] = 0;
		xQueueSendToBack(myQueue01Handle, &tx, 0);
		
}

//解算部分
uint8_t attitudeGetAngle_get(const MecArmAttiSturcture S, float *ptheta)
{
	
	float L1 = 0.20; //杆长
	float L2 = 0.12;
	float L3 = 0.13;
	float alpha, beta, lp, By, Bz;
	By = S.pointY-L3; //这里设置γ为-90
	Bz = S.pointZ;
	lp = By*By + Bz*Bz;
	
	if (sqrt(lp)>=L1+L2 || sqrt(lp)<=fabs(L1-L2))
		return 1;
	if (S.mode == 1)
		return 1;
	alpha = atan2(Bz,By);
	
	beta = acos((L1*L1+lp-L2*L2)/(2.0*L1*sqrt(lp))); //这里使用弧度制

	ptheta[0] = (-(pi/2.0-alpha-beta))*180.f/pi;								//1号舵机角度
	ptheta[1] = (acos((L1*L1+L2*L2-lp)/(2*L1*L2))-pi)*180.f/pi;	//2号舵机角度
	ptheta[2] = (-ptheta[0] -ptheta[1]- 90);										//3号舵机角度,注意ptheta2是角度制了
	ptheta[3] = (atan2(S.pointX, S.pointY))*180.f/pi;						//云台舵机角度
	ptheta[4] = S.clip_angle;
	return 0;
}

uint8_t attitudeGetAngle_put(const MecArmAttiSturcture S, float *ptheta)
{

	float L1 = 0.20; //杆长
	float L2 = 0.12;
	float L3 = 0.13;
	float alpha, beta, lp, By, Bz;
	By = S.pointY; //这里设置γ为-90
	Bz = S.pointZ + L3;
	lp = By*By + Bz*Bz;
	if (sqrt(lp)>=L1+L2 || sqrt(lp)<=fabs(L1-L2))
		return 1;
	if (S.mode == 0)
		return 1;
	alpha = atan2(Bz,By);
	beta = acos((L1*L1+lp-L2*L2)/(2*L1*sqrt(lp))); //这里使用弧度制,注意除法的类型转换，以及转换为角度制
	ptheta[0] = (-(pi/2.0-alpha-beta))*180.f/pi;
	ptheta[1] = (acos((L1*L1+L2*L2-lp)/(2*L1*L2))-pi)*180.f/pi;
	ptheta[2] = (-ptheta[0] -ptheta[1]- 180);
	ptheta[3] = (atan2(S.pointX, S.pointY))*180.f/pi;
	ptheta[4] = S.clip_angle;
	return 0;
}
	
uint8_t Move_Servo(float servo1_angle,float servo2_angle,float servo3_angle,float servo4_angle,uint32_t time1,uint32_t time2,uint32_t time3,uint32_t time4)
{
	uint32_t time_last=HAL_GetTick();
	float arr=0;
	while ( fabs(servo1_angle-servoRefAngle[0]) >=1 || fabs(servo2_angle-servoRefAngle[1]) >=1 || fabs(servo3_angle-servoRefAngle[2]) >=3 || fabs(servo4_angle-servoRefAngle[3]) >=1 )
	{
		uint32_t time_now=HAL_GetTick();
		uint32_t time_data=time_now-time_last;
		if (time_data >= time1)
		{
		if(servo1_angle-servoRefAngle[0] >=1 )
		{		
				servoRefAngle[0]++;
				arr = 2.3*servoRefAngle[0] + 315;
				TIM2->CCR1 = arr;
		}
		else if(servoRefAngle[0]-servo1_angle >=1 )
		{
				servoRefAngle[0]--;
				arr = 2.3*servoRefAngle[0] + 315;
				TIM2->CCR1 = arr;
		} 
		}	
		
				if (time_data >= time2)
		{
		if(servo2_angle-servoRefAngle[1] >=1 )
		{		
				servoRefAngle[1]++;
				arr = 2.3*servoRefAngle[1] + 524;
				TIM2->CCR2 = arr;
		}
		else if(servoRefAngle[1]-servo2_angle >=1 )
		{
				servoRefAngle[1]--;
				arr = 2.3*servoRefAngle[1] + 524;
				TIM2->CCR2 = arr;
		}
		}
		
		
				if (time_data >= time3)
		{
		if(servo3_angle-servoRefAngle[2] >=3 )
		{		
				servoRefAngle[2]+=3;
				arr = 2.3*servoRefAngle[2] + 315;
				TIM2->CCR3 = arr;
		}
		else if(servoRefAngle[2]-servo3_angle >=3 )
		{
				servoRefAngle[2]-=3;
				arr = 2.3*servoRefAngle[2] + 315;
				TIM2->CCR3 = arr;
		}
		}
		
		
				if (time_data >= time4)
		{
		if(servo4_angle-servoRefAngle[3] >=1 )
		{		
				servoRefAngle[3]++;
				arr = 2.3*servoRefAngle[3] + 315;
				TIM2->CCR4 = arr;
		}
		else if(servoRefAngle[3]-servo4_angle >=1 )
		{
				servoRefAngle[3]--;
				arr = 2.3*servoRefAngle[3] + 315;
				TIM2->CCR4 = arr;
		}
		}
				vTaskDelay(20);
	}
}
