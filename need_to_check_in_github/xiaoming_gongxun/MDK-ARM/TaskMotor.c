#include "TaskMotor.h"
#include "myqueue.h"
#include "FreeRTOS.h"
#include "math.h"
#include "bsp_imu.h"
#include "TaskMearm.h"
#include "TaskAction.h"

#define ABS(x)	( (x>0) ? (x) : (-x) )
PID_TypeDef motor_ppid[4];
PID_TypeDef motor_vpid[4];	// motor vpid
PID_TypeDef angle_pid;			// angle pid
PID_TypeDef line_pid[4];			// angle pid

float distance[3] ={0};
extern float yaw0;
//  Initialization
struct mecanum chassis ={0, 0, 0, 0,0,0};
struct mecanum *pchassis = &chassis;
extern imu_t imu;
extern float imu_total_yaw;
char buf[300];
int rpm=0;
int count;	
uint8_t aRxBuffer[4]= {0x01,0x01,0x02,0x03};    //字符存放全局单元	transmit
uint8_t receiveCode[7];
uint8_t receiveColor[3];
uint8_t receiveCircle[7];
uint16_t TIM_COUNT[2];
extern int Xpositon,Ypositon;
extern float Xoffset,Yoffset,Zoffset;
//接收消息
extern QueueHandle_t bottom_moveHandle;
extern UART_HandleTypeDef huart2;
POSITON pos_rec[8];

void Waitfinishmoving()
{
	vTaskDelay(200);
	while(1)
	{	
		rpm=0;
		for(int i =0;i<4;i++)
			rpm += abs(moto_chassis[i].speed_rpm);
		float rpm_sum = rpm/4.0;
		//printf("%f\r\n",rpm_sum);
		if(rpm_sum < 30)
			break;
	}
	vTaskDelay(200);
}

void GetYaw()
{
		mpu_get_data();
		imu_ahrs_update();
		imu_attitude_update(); 
}

void GotoXYZ(float x,float y,float angle)		//  x:right ;  y: front! 
{		
		GetYaw();
		yaw0=imu.yaw;	// get_total_yaw之前必须先初始化yaw0
	
		float new_target[4]= {x-y+moto_chassis[0].total_angle*1.0f/8192.f/36.f*76*PI,x+y+moto_chassis[1].total_angle*1.0f/8192.f/36.f*76*PI,-x+y+moto_chassis[2].total_angle*1.0f/8192.f/36.f*76*PI,-x-y+moto_chassis[3].total_angle*1.0f/8192.f/36.f*76*PI};
		float t=HAL_GetTick();
		while(1)
		{
				if(fabs(new_target[0]-(moto_chassis[0].total_angle*1.0f/8192.f/36.f*76*PI))<5 ||HAL_GetTick()-t>6000)					
				{
					set_moto_current(&hcan1,0,0,0,0); 	
					//HAL_Delay(50);
					vTaskDelay(10);
					break;
				}
		//  更新陀螺仪数据：
				imu_get_total_angle();
				printf("%f\r\n",fabs(yaw0));
		//	位置环：	
				for(int i=0; i<4; i++)
				{		
					motor_ppid[i].target = new_target[i];					
					pid_calculate(&motor_ppid[i],moto_chassis[i].total_angle*1.0f/8192.f/36.f*76*PI);						//PID calculate	
				}			
				angle_pid.target=angle;
				pid_calculate(&angle_pid,imu_total_yaw);			
		//  速度环：
				pchassis->zw_deg_s=angle_pid.output;
				mecanum_calculate(pchassis);
				for(int i=0; i<4; i++)
				{	
					motor_vpid[i].target = motor_ppid[i].output + pchassis->wheel_rpm[i];
					pid_calculate(&motor_vpid[i],moto_chassis[i].speed_rpm);						//PID calculate	
				}
				set_moto_current(&hcan1, motor_vpid[0].output,motor_vpid[1].output,motor_vpid[2].output,motor_vpid[3].output);					
				vTaskDelay(10);
		}	
}

void GotoXY(float x,float y)		//  x:right ;  y: front!
{				
		float new_target[4]= {x-y,x+y,-x+y,-x-y};
		for(int i=0; i<4; i++)
		{
			motor_vpid[i].target = new_target[i]*8;	
			pid_calculate(&motor_vpid[i],moto_chassis[i].speed_rpm);						//PID calculate	
		}
		set_moto_current(&hcan1, motor_vpid[0].output,motor_vpid[1].output,motor_vpid[2].output,motor_vpid[3].output);
		vTaskDelay(30);
}

void position_correct(void)		//  x:right ;  y: front! 
{		
		uint8_t cmd = '5';
		float t=HAL_GetTick();
		while(1)
		{
			if(HAL_GetTick()-t>2500)					
					{
					set_moto_current(&hcan1,0,0,0,0); 	
					vTaskDelay(10);
					break;
					}		
		HAL_UART_Transmit(&huart2,&cmd,sizeof(cmd),100000);		
		GotoXY( -Xpositon, Ypositon);		//  x:right ;  y: front!1	
		}	
			
}
void round_correct(void)		//  x:right ;  y: front! 
{		
		uint8_t cmd = '3';
		float t=HAL_GetTick();
		while(1)
		{
			if(HAL_GetTick()-t>3000)					
					{
					set_moto_current(&hcan1,0,0,0,0); 	
					vTaskDelay(10);
					break;
					}		
		HAL_UART_Transmit(&huart2,&cmd,sizeof(cmd),100000);		
		GotoXY(-Xoffset, Yoffset);		//  x:right ;  y: front!1	
		}				
}

void round_correct2(int mode)
{
		uint8_t cmd;
		if(mode==1)
			cmd = '3';
		else if(mode==2)
			cmd = '7';
		float t=HAL_GetTick();
		while(1)
		{
			if(HAL_GetTick()-t>2300)					
					{
					set_moto_current(&hcan1,0,0,0,0); 	
					vTaskDelay(10);
					break;
					}		
		HAL_UART_Transmit(&huart2,&cmd,sizeof(cmd),100000);		
		GotoXY(-Yoffset, -Xoffset);		//  x:right ;  y: front!1	
		}				
}

void correct_xyz(float x,float y,float z)
{
	float new_target[4]= {x-y,x+y,-x+y,-x-y};		
	if(z==0)
	{
		vTaskDelay(40);
		return;
	}
	float offset=1.20;		
	for(int i=0; i<4; i++)
	{	
		line_pid[i].target = offset;	
		pid_calculate(&line_pid[i],z);						//PID calculate	
	}
	
	for(int i=0; i<4; i++)
	{	
		motor_vpid[i].target = line_pid[i].output+new_target[i]*10;	
		pid_calculate(&motor_vpid[i],moto_chassis[i].speed_rpm);						//PID calculate	
	}
	set_moto_current(&hcan1, motor_vpid[0].output,motor_vpid[1].output,motor_vpid[2].output,motor_vpid[3].output);
	//vTaskDelay(40);
}

void correct2(void)
{
		uint8_t cmd1 = '3';
		uint8_t cmd2 = '4';
		float t=HAL_GetTick();
		while(1)
		{
			if(HAL_GetTick()-t>2300)					
					{
					set_moto_current(&hcan1,0,0,0,0); 	
					vTaskDelay(10);
					break;
					}		
		HAL_UART_Transmit(&huart2,&cmd1,sizeof(cmd1),100000);	
		vTaskDelay(40);		
		HAL_UART_Transmit(&huart2,&cmd2,sizeof(cmd2),100000);		
		correct_xyz(-Yoffset,-Xoffset,Zoffset);		//  x:right ;  y: front!1	
		}				
}

void GotoY(float y)		//  x:right ;  y: front!
{				
		float new_target[4]= {-y+moto_chassis[0].total_angle*1.0f/8192.f/36.f*76*PI,y+moto_chassis[1].total_angle*1.0f/8192.f/36.f*76*PI,y+moto_chassis[2].total_angle*1.0f/8192.f/36.f*76*PI,-y+moto_chassis[3].total_angle*1.0f/8192.f/36.f*76*PI};
		float t=HAL_GetTick();
		while(1)
		{
			if(fabs(new_target[0]-(moto_chassis[0].total_angle*1.0f/8192.f/36.f*76*PI))<5)					
					{
					set_moto_current(&hcan1,0,0,0,0); 	
					vTaskDelay(10);
					break;
					}
					
				for(int i=0; i<4; i++)
				{		
					motor_ppid[i].target = new_target[i];					
					pid_calculate(&motor_ppid[i],moto_chassis[i].total_angle*1.0f/8192.f/36.f*76*PI);						//PID calculate	
				}							

				for(int i=0; i<4; i++)
				{	
					motor_vpid[i].target = motor_ppid[i].output;	
					pid_calculate(&motor_vpid[i],moto_chassis[i].speed_rpm);						//PID calculate	
				}
				set_moto_current(&hcan1, motor_vpid[0].output,motor_vpid[1].output,motor_vpid[2].output,motor_vpid[3].output);				
				vTaskDelay(10);
		}	
}

void GotoZ(float z)
{		
		if(z==0)
		{
			vTaskDelay(40);
			return;
		}
		float offset=1.20;
		float new_target[4]= {-z+offset,-z+offset,-z+offset,-z+offset};
		
		for(int i=0; i<4; i++)
		{	
			line_pid[i].target = offset;	
			pid_calculate(&line_pid[i],z);						//PID calculate	
		}
		
		for(int i=0; i<4; i++)
		{	
			motor_vpid[i].target = line_pid[i].output;	
			pid_calculate(&motor_vpid[i],moto_chassis[i].speed_rpm);						//PID calculate	
		}
		set_moto_current(&hcan1, motor_vpid[0].output,motor_vpid[1].output,motor_vpid[2].output,motor_vpid[3].output);
		vTaskDelay(40);
}

void line_correct(int angle)
{
		uint8_t cmd = '4';
		MecArmAttiSturcture CaptureAtti_line ={0,   angle,    0.29,    0.15,    -4,     {0, 0, 0, 0}};
		Mearm_Move(CaptureAtti_line);
		GM_detect();
		vTaskDelay(600);
		GM_kd(1);//locked
		float t=HAL_GetTick();
		while(1)
		{
			if(HAL_GetTick()-t>2800)					
					{
					set_moto_current(&hcan1,0,0,0,0); 	
					vTaskDelay(30);
					break;
					}
		HAL_UART_Transmit(&huart2,&cmd,sizeof(cmd),100000);		
		GotoZ(Zoffset);		//  x:right ;  y: front!1	
		}
		GM_kd(0); //unlocked
}


void GotoX(float x)		//  x:right ;  y: front!
{			
	float new_target[4]= {x+moto_chassis[0].total_angle*1.0f/8192.f/36.f*76*PI,x+moto_chassis[1].total_angle*1.0f/8192.f/36.f*76*PI,-x+moto_chassis[2].total_angle*1.0f/8192.f/36.f*76*PI,-x+moto_chassis[3].total_angle*1.0f/8192.f/36.f*76*PI};
	float t=HAL_GetTick();
		while(1)
		{
			if(fabs(new_target[0]-(moto_chassis[0].total_angle*1.0f/8192.f/36.f*76*PI))<5)					
					{
					set_moto_current(&hcan1,0,0,0,0); 	
					vTaskDelay(10);
					break;
					}
					
				for(int i=0; i<4; i++)
				{		
					motor_ppid[i].target = new_target[i];					
					pid_calculate(&motor_ppid[i],moto_chassis[i].total_angle*1.0f/8192.f/36.f*76*PI);						//PID calculate	
				}							

				for(int i=0; i<4; i++)
				{	
					motor_vpid[i].target = motor_ppid[i].output;	
					pid_calculate(&motor_vpid[i],moto_chassis[i].speed_rpm);						//PID calculate	
				}
				set_moto_current(&hcan1, motor_vpid[0].output,motor_vpid[1].output,motor_vpid[2].output,motor_vpid[3].output);		
				vTaskDelay(10);
		}					
}


	/*< 初始化PID参数 >*/
void pid_para(void)
{
	for(int i=0; i<4; i++)
  {	
    pid_init(&motor_ppid[i]);
		motor_ppid[i].f_param_init(&motor_ppid[i],PID_Position,6000,50,0,0,10000,0,15,1.2,0.2);  
  }
	
  for(int i=0; i<4; i++)
  {	
    pid_init(&motor_vpid[i]);
    motor_vpid[i].f_param_init(&motor_vpid[i],PID_Speed,18000,1400,10,0,10000,0,2.3,0.6,0);   
		moto_chassis[i].total_angle=0;
	}
		
  for(int i=0; i<4; i++)
  {	
    pid_init(&line_pid[i]);
    line_pid[i].f_param_init(&line_pid[i],PID_Speed,6000,80,0,0,10000,0,100,2.5,0.1);
	}
	
	pid_init(&angle_pid);
	angle_pid.f_param_init(&angle_pid,PID_Position,30,2,0,0,10,0,3,0,0); 
//PID参数初始化:
//struct _PID_TypeDef *pid, PID_ID id, uint16_t maxOutput, uint16_t integralLimit, float deadband, 
// uint16_t controlPeriod, int16_t max_err, int16_t  target, float kp, float ki, float kd);
}

//执行部分
void Task_Motor(void)
{
	
	if(xQueueReceive(bottom_moveHandle, &pos_rec[0], portMAX_DELAY))
	{
		GotoXYZ(pos_rec[0].x,pos_rec[0].y,0);//pos_rec[0].angle);		
	}
}
