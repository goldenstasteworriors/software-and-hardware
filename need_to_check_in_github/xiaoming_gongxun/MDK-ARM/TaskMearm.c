#include "TaskMearm.h"
#include "tim.h"
#include "math.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "myqueue.h"
#include "TaskMotor.h"
#include "bsp_can.h"
#include "TaskAction.h"
#define pi 3.1415926
#define	Song +12
#define Jing -14
float servoAngle[5] = {0, -112, -10, 0, 0};
float servoRefAngle[4] = {0, 7, -74, -23};
extern QueueHandle_t	ArmAttitudeQueueHandle;
extern QueueHandle_t G6020AngleQueueHandle;
MecArmAttiSturcture  tx;
MecArmAttiSturcture  R;
PID_TypeDef GM_vpid,GM_ppid;
float gm_data;
float gm_kd = 0.36;
void GM_init(void)
{
		pid_init(&GM_vpid);
    GM_vpid.f_param_init(&GM_vpid, PID_Speed,7600, 300,0,0,8000,0,70,0.1, 2);
		pid_init(&GM_ppid);
    GM_ppid.f_param_init(&GM_ppid, PID_Position, 140, 8,0,0,8000,0, 0.36, 0.05, 0.36);
		if(moto_chassis[4].total_angle<0)			//Angle Init
				moto_chassis[4].round_cnt+=1;
}

void rm_servo(void)
{
	static float angle = 180*8192.0f/360.0f;
	if(xQueueReceive(G6020AngleQueueHandle, &gm_data, 0))
	{
		angle=gm_data*8192.0f/360.0f;
	}
	GM_ppid.target = angle;	
	pid_calculate(&GM_ppid,moto_chassis[4].total_angle);
	GM_vpid.target = GM_ppid.output;	
	pid_calculate(&GM_vpid,moto_chassis[4].speed_rpm);
	set_motor_voltage(&hcan1,GM_vpid.output,0,0,0);
}

void clip(double angle)
{
		//大疆板子对应APB1外设，时钟频率对应36Mhz
		//三线舵机占空比为2.5%到12.5%，最小值为3599*2.5%=89.975 最大值为3599*12.5%=449.875
		//对应角度 ccr = 0.5*angle + 179
		float arr ;
		arr = 2.3*angle + 315;
		TIM4->CCR4 = arr;

}

void GM_detect(void)
{
	while(1)
	{
		if(fabs(servoAngle[3]*8192.0f/360.0f-moto_chassis[4].total_angle)-90.0f<0)
		{
			break;
		}
	}
}

void try1(void)		//抓槽
{
	//机械臂的运动位置											mode  GM_angle pointY	 pointZ   clip 														
	const MecArmAttiSturcture CaptureAtti_1 ={1,   180,    0.072,    0.03,    Jing,     {0, 0, 0, 0}};
	Mearm_Move(CaptureAtti_1);
}

void init_pos(void)
{
	//机械臂的运动位置											mode  GM_angle pointY	 pointZ   clip 														
	const MecArmAttiSturcture CaptureAtti_1 ={0,   180,    0.20,    0.20,    Song,     {0, 0, 0, 0}};
	Mearm_Move(CaptureAtti_1);	
}

void zhua_detect(void)
{
	//机械臂的运动位置											mode  GM_angle pointY	 pointZ   clip 														
	const MecArmAttiSturcture CaptureAtti_1 ={0,   176,    0.28,    0.20,    Song,     {0, 0, 0, 0}};
	Mearm_Move(CaptureAtti_1);	
}

void shou(int angle)		
{
	//机械臂的运动位置											mode  GM_angle pointY	 pointZ   clip 														
	const MecArmAttiSturcture CaptureAtti_1 ={1,   angle,    0.076,    0.08,    Song,     {0, 0, 0, 0}};
	Mearm_Move(CaptureAtti_1);
}

//Put_on circle 部分动作
//三套y,z，对应三个区域		半加工(0.27,0.01) 原料区(0.27,0.06)  精加工(0.27,0.01)
void move_get_fang(int put_angle,float y, float z)		
{
	MecArmAttiSturcture CaptureAtti_8_3 ={0,   put_angle,    0.23,    0.15,   Jing,     {0, 0, 0, 0}};
	Mearm_Move(CaptureAtti_8_3);
	GM_detect();
	vTaskDelay(200);
	//机械臂的运动位置											mode  GM_angle 			pointY	 pointZ   clip 											
	MecArmAttiSturcture CaptureAtti_3 ={0,   put_angle,    y,    z+0.08f,    Jing,     {0, 0, 0, 0}};
	Mearm_Move(CaptureAtti_3);
	vTaskDelay(600);
	mearm_z(CaptureAtti_3,-0.08);
	vTaskDelay(80);
	MecArmAttiSturcture CaptureAtti_3_2 ={0,   put_angle,    y,   z,    Song,     {0, 0, 0, 0}};
	Mearm_Move(CaptureAtti_3_2);
	vTaskDelay(380);
	mearm_y(CaptureAtti_3_2,-0.02);
	MecArmAttiSturcture CaptureAtti_3_3 ={0,   put_angle,    y-0.02f,   z,    Song,     {0, 0, 0, 0}};
	mearm_z(CaptureAtti_3_3,0.078);
	vTaskDelay(100);
	MecArmAttiSturcture CaptureAtti_3_4 ={0,   put_angle,    y-0.05f,   z+0.14f,    Song,     {0, 0, 0, 0}};
	Mearm_Move(CaptureAtti_3_4);
	vTaskDelay(350);

}
void move_turn_put(int put_pos)		//爪子紧，//固定y,z
{
	//机械臂的运动位置											mode  GM_angle 			pointY	 pointZ   clip 														
	MecArmAttiSturcture CaptureAtti_5 ={0,   put_pos,    0.3,    0.15,    Jing,     {0, 0, 0, 0}};
	Mearm_Move(CaptureAtti_5);		
}
void move_turn_song(int put_pos)		//爪子松，//固定y,z
{
	//机械臂的运动位置											mode  GM_angle 			pointY	 pointZ   clip 														
	MecArmAttiSturcture CaptureAtti_51 ={0,   put_pos,    0.3,    0.15,    Song,     {0, 0, 0, 0}};
	Mearm_Move(CaptureAtti_51);		
}


//GRAB_UP部分动作
void back_grab(int put_angle,float y, float z)		
{
	//机械臂的运动位置											mode  GM_angle pointY	 pointZ   clip 														
	MecArmAttiSturcture CaptureAtti_1 ={0,   put_angle,    y-0.032f ,    z+0.08f,    Song,     {0, 0, 0, 0}};
	Mearm_Move(CaptureAtti_1);
	vTaskDelay(200);
	mearm_z(CaptureAtti_1,-0.08);
	MecArmAttiSturcture CaptureAtti_2 ={0,   put_angle,    y-0.032f ,    z,    Song,     {0, 0, 0, 0}};	
	mearm_y(CaptureAtti_2,0.033);
	vTaskDelay(200);
}

void back_grab_2(int put_angle,float y, float z)		
{
	//机械臂的运动位置											mode  GM_angle pointY	 pointZ   clip 		
	shou(put_angle);	
	GM_detect();
	MecArmAttiSturcture CaptureAtti_1_2 ={0,   put_angle,    y-0.02f ,    z+0.10f,    Song,     {0, 0, 0, 0}};				
	Mearm_Move(CaptureAtti_1_2);
	vTaskDelay(560);
	MecArmAttiSturcture CaptureAtti_1_3 ={0,   put_angle,    y-0.016f ,    z+0.08f,    Song,     {0, 0, 0, 0}};
	Mearm_Move(CaptureAtti_1_3);
	vTaskDelay(200);
	mearm_z(CaptureAtti_1_3,-0.075);
	vTaskDelay(100);
	MecArmAttiSturcture CaptureAtti_1_4 ={0,   put_angle,    y-0.016f ,    z+0.005f,    Song,     {0, 0, 0, 0}};
	mearm_y(CaptureAtti_1_4,0.025);
	vTaskDelay(100);

}

void move_get_zhua(int put_angle,float y, float z)		
{
	//机械臂的运动位置											mode   GM_angle 	pointY pointZ  clip 														
	MecArmAttiSturcture CaptureAtti_3 ={0,   put_angle,    y,    z+0.005,    Jing,     {0, 0, 0, 0}};
	Mearm_Move(CaptureAtti_3);
	vTaskDelay(200);
}

void move_get_zhua2(int put_angle,float y, float z)		
{
	//机械臂的运动位置								mode   GM_angle 			pointY	 pointZ	  clip 														
	MecArmAttiSturcture CaptureAtti_3 ={0,   put_angle,    y+0.009f,    z+0.010f,    Jing,     {0, 0, 0, 0}};
	Mearm_Move(CaptureAtti_3);
	vTaskDelay(200);
}

void move_put(int put_pos)		////固定y,z
{
	//机械臂的运动位置								mode  GM_angle 		pointY	 pointZ   clip 
	MecArmAttiSturcture CaptureAtti_6 ={1,   put_pos,    0.0763,    0.08,   Jing,     {0, 0, 0, 0}};	
	Mearm_Move(CaptureAtti_6);
	GM_detect();
	vTaskDelay(500);
	mearm_z(CaptureAtti_6,-0.053);	
	vTaskDelay(500);
	MecArmAttiSturcture CaptureAtti_6_2 ={1,   put_pos,    0.0763,    0.027,   Song,     {0, 0, 0, 0}};
	Mearm_Move(CaptureAtti_6_2);
	vTaskDelay(200);
	mearm_z(CaptureAtti_6_2,0.053);
	vTaskDelay(100);
}

void up_grab(int put_angle,float y)		
{
	//机械臂的运动位置											mode  GM_angle 			pointY	 pointZ   clip 														
	MecArmAttiSturcture CaptureAtti_4 ={1,   put_angle,     0.13,    0.08,   Jing,     {0, 0, 0, 0}};
	Mearm_Move(CaptureAtti_4);	
	vTaskDelay(200);
}

void move_turn_grab(int put_pos)		//爪子紧，//固定y,z
{
	//机械臂的运动位置											mode  GM_angle 			pointY	 pointZ   clip 														
	MecArmAttiSturcture CaptureAtti_5 ={0,   put_pos,    0.2,    0.15,    Jing,     {0, 0, 0, 0}};
	Mearm_Move(CaptureAtti_5);		
}
void move_put_up(int put_pos)	//固定y,z
{
		//机械臂的运动位置											mode  GM_angle 	pointY	 pointZ   clip 
	MecArmAttiSturcture CaptureAtti_7 ={0,   put_pos,    0.3,    0.15,   Song,     {0, 0, 0, 0}};
	Mearm_Move(CaptureAtti_7);
}




//从车上抓
void move_grap(int put_pos)		//固定y,z
{
			//机械臂的运动位置											mode  GM_angle pointY	 pointZ   clip 
	MecArmAttiSturcture CaptureAtti_8 ={1,   put_pos,    0.075,    0.08,   Song,     {0, 0, 0, 0}};
	Mearm_Move(CaptureAtti_8);
	GM_detect();
	vTaskDelay(360);
	mearm_z(CaptureAtti_8,-0.053);	
	MecArmAttiSturcture CaptureAtti_8_2 ={1,   put_pos,    0.075,    0.027,   Jing,     {0, 0, 0, 0}};
	Mearm_Move(CaptureAtti_8_2);
	vTaskDelay(200);
	mearm_z(CaptureAtti_8_2,0.053);
	vTaskDelay(100);
	
}
void move_grap_up0(int put_pos)		////固定y,z
{
			//机械臂的运动位置											mode  GM_angle pointY	 pointZ   clip 
	const MecArmAttiSturcture CaptureAtti_9 ={0,   put_pos,    0.068,    0.1,   Jing,     {0, 0, 0, 0}};
	Mearm_Move(CaptureAtti_9);
}
void move_grap_up(int put_pos)		//固定y,z
{
			//机械臂的运动位置											mode  GM_angle pointY	 pointZ   clip 
	const MecArmAttiSturcture CaptureAtti_9 ={0,   put_pos,    0.3,    0.15,   Jing,     {0, 0, 0, 0}};
	Mearm_Move(CaptureAtti_9);
}

//解算部分
uint8_t attitudeGetAngle_get(const MecArmAttiSturcture S, float *ptheta)
{
	if (S.mode == 1||S.mode == 3)
		return 1;
	float L1 = 0.213; //杆长,0.2  0.12  0.13
	float L2 = 0.13;
	float L3 = 0.095;
	float alpha, beta, lp, By, Bz;
	By = S.pointY-L3; //这里设置γ为-90
	Bz = S.pointZ;
	lp = By*By + Bz*Bz;
	
	if (sqrt(lp)>=L1+L2 || sqrt(lp)<=fabs(L1-L2))
		return 1;
//	if(lp < 0.1f)
//		return 1;

	alpha = atan2(Bz,By);
	
	beta = acos((L1*L1+lp-L2*L2)/(2.0f*L1*sqrt(lp))); //这里使用弧度制

	ptheta[0] = (-(pi/2.0-alpha-beta))*180.f/pi;								//1号舵机角度
	ptheta[1] = (acos((L1*L1+L2*L2-lp)/(2*L1*L2))-pi)*180.f/pi;	//2号舵机角度
	ptheta[2] = (-ptheta[0] -ptheta[1]- 90);										//3号舵机角度,注意ptheta2是角度制了
	ptheta[3] = S.GM_angle;						//云台舵机角度
	ptheta[4] = S.clip_angle;
	return 0;
}

uint8_t attitudeGetAngle_put(const MecArmAttiSturcture S, float *ptheta)
{
	if (S.mode == 0||S.mode == 2)
		return 1;
	float L1 = 0.213; //杆长
	float L2 = 0.13;
	float L3 = 0.095;
	float alpha, beta, lp, By, Bz;
	By = S.pointY; //这里设置γ为-90
	Bz = S.pointZ + L3;
	lp = By*By + Bz*Bz;
	if (sqrt(lp)>=L1+L2 || sqrt(lp)<=fabs(L1-L2))
		return 1;
//	if(lp < 0.1f)
//		return 1;

	alpha = atan2(Bz,By);
	beta = acos((L1*L1+lp-L2*L2)/(2*L1*sqrt(lp))); //这里使用弧度制,注意除法的类型转换，以及转换为角度制
	ptheta[0] = (-(pi/2.0-alpha-beta))*180.f/pi;
	ptheta[1] = (acos((L1*L1+L2*L2-lp)/(2*L1*L2))-pi)*180.f/pi;
	ptheta[2] = (-ptheta[0] -ptheta[1]- 180);
	ptheta[3] = S.GM_angle;
	ptheta[4] = S.clip_angle;
	return 0;
}
	
void Move_Servo(float servo1_angle,float servo2_angle,float servo3_angle,uint32_t time1,uint32_t time2,uint32_t time3,uint32_t time4)
{
	uint32_t time_last=HAL_GetTick();
	float arr=0;
	while ( fabs(servo1_angle-servoRefAngle[0]) >=1 || fabs(servo2_angle-servoRefAngle[1]) >=1 || fabs(servo3_angle-servoRefAngle[2]) >=3 )
	{
		uint32_t time_now=HAL_GetTick();
		uint32_t time_data=time_now-time_last;
		if (time_data >= time1)
		{
			if(servo1_angle-servoRefAngle[0] >=1 )
			{		
				servoRefAngle[0]++;
				arr = 1.54f*servoRefAngle[0] + 244.8;
				TIM4->CCR1 = arr;
				vTaskDelay(6);
			}
			else if(servoRefAngle[0]-servo1_angle >=1 )
			{ 
				servoRefAngle[0]--;
				arr = 1.54f*servoRefAngle[0] + 244.8;
				TIM4->CCR1 = arr;
				vTaskDelay(6);
			} 
		}	
		
		if (time_data >= time2)
		{
			if(servo2_angle-servoRefAngle[1] >=1 )
			{		
				servoRefAngle[1]++;
				arr = 2.3f*servoRefAngle[1] + 524;
				TIM4->CCR2 = arr;
				vTaskDelay(2);
			}
			else if(servoRefAngle[1]-servo2_angle >=1 )
			{
				servoRefAngle[1]--;
				arr = 2.3f*servoRefAngle[1] + 524;
				TIM4->CCR2 = arr;
				vTaskDelay(2);
			}
		}
			
		if (time_data >= time3)
		{
			if(servo3_angle-servoRefAngle[2] >=1 )
			{		
					servoRefAngle[2]+=1;
					arr = 2.3f*servoRefAngle[2] + 315;
					TIM4->CCR3 = arr;
					vTaskDelay(2);
			}
			else if(servoRefAngle[2]-servo3_angle >=1 )
			{
					servoRefAngle[2]-=1;
					arr = 2.3f*servoRefAngle[2] + 315;
					TIM4->CCR3 = arr;
					vTaskDelay(2);
			}
		}
		
		
//			if (time_data >= time4)
//		{
//			if(servo4_angle-servoRefAngle[3] >=1 )
//			{		
//					servoRefAngle[3]++;
//					arr = 2.3f*servoRefAngle[3] + 315;
//					TIM2->CCR4 = arr;
//			}
//			else if(servoRefAngle[3]-servo4_angle >=1 )
//			{
//					servoRefAngle[3]--;
//					arr = 2.3f*servoRefAngle[3] + 315;
//					TIM2->CCR4 = arr;
//			}
//		}
//				vTaskDelay(20);
	}
}

//执行部分
void Task_Mearm(void)
{	
//			TickType_t xLastWakeTime;
//			xLastWakeTime = xTaskGetTickCount();
				if(xQueueReceive(ArmAttitudeQueueHandle, &R, portMAX_DELAY))
			{
				if(R.mode == 0||R.mode == 1)
				{
					if(attitudeGetAngle_get(R, servoAngle) != 1)//0
					{
						xQueueSendToBack(G6020AngleQueueHandle, &servoAngle[3], 0);			//将云台的角度发送出
						while(1)
						{
							//vTaskDelay(5);
							//printf("d");
							if(fabs(servoAngle[3]*8192.0f/360.0f-moto_chassis[4].total_angle)-80.0f<0)
							{
								Move_Servo(servoAngle[0]+0.5,servoAngle[1],-servoAngle[2]-5.8f,0,0,0,0);
								clip(servoAngle[4]);	
								break;							
							}
						}
					}
					if(attitudeGetAngle_put(R, servoAngle) != 1)
					{
						xQueueSendToBack(G6020AngleQueueHandle, &servoAngle[3], 0);	
						while(1)
						{
								if(fabs(servoAngle[3]*8192.0f/360.0f-moto_chassis[4].total_angle)-80.0f<0)
								{
								Move_Servo(servoAngle[0]+0.5,servoAngle[1],-servoAngle[2]+5.3f ,0,0,0,0);				
								clip(servoAngle[4]);	
								break;
								}
						}
					}
				}
				else if(R.mode == 2)
				{
						xQueueSendToBack(G6020AngleQueueHandle, &R.GM_angle, 0);			//将云台的角度发送出
				}
				else if(R.mode == 3)
				{
						Move_Servo(R.GM_angle,R.pointY,-R.pointZ+3,0,0,0,0);	
				}
			}
}

void mearm_y(MecArmAttiSturcture S,float y)
{
	if(y>=0)
	{
				for(int i=0;i<(y*1000);i++)
			{
					Mearm_Move(S);	
					S.pointY+=0.001f;
					vTaskDelay(10);
			}
	}
	else
	{
					for(int i=0;i<(-y*1000);i++)
			{
					Mearm_Move(S);	
					S.pointY-=0.001f;
					vTaskDelay(10);
			}	
	}
}

void mearm_z(MecArmAttiSturcture S,float z)
{
	if(z>=0)
	{
				for(int i=0;i<(z*1000);i++)
			{
					Mearm_Move(S);	
					S.pointZ+=0.001f;
					vTaskDelay(10);
			}
	}
	else
	{
					for(int i=0;i<(-z*1000);i++)
			{
					Mearm_Move(S);	
					S.pointZ-=0.001f;
					vTaskDelay(10);
			}	
	}
}
void GM_kd(int mode)
{
	if(mode==1)
	{	
    GM_vpid.f_param_init(&GM_vpid, PID_Speed,13600, 300,0,0,8000,0,110,0.1, 2);
		GM_ppid.f_param_init(&GM_ppid, PID_Position, 200, 8,0,0,8000,0, 1.0, 0.05, 0.3);
	}
		else
	{	
    GM_vpid.f_param_init(&GM_vpid, PID_Speed,9500, 300,0,0,8000,0,70,0.1, 2);
		GM_ppid.f_param_init(&GM_ppid, PID_Position, 160, 8,0,0,8000,0, 0.36, 0.05, 0.36);
	}
	vTaskDelay(10);
}
void mearm_init(void)
{
		for(int i = 0; i < 4; i++)
	{
		servoRefAngle[i] = servoAngle[i];
	}
}
