#include "main.h"
#include "pid.h"
#include "can1.h"
#include "can2.h"
#include "remote.h"
#include "chassis_task.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "tim.h"

int vx, vy, vw;
int vx_set, vy_set;
int w_offset_cnt;
int w_all_offset;	
int key_mode_use_chassis_flag;
uint32_t Chassis_high_water;
pid_Typedef chassis_vel_pid[4];
pid_Typedef chassis_pos_follow_pid = {
	.P = 0.25f,
	.I = 0.00065f,
	.D = 0.3f,
	.IMax = 100.0f,
	.SetPoint = 0.0f
};
pid_Typedef chassis_vel_follow_pid = {
	.P = 1750.0f,
	.I = 0.0f,
	.D = 150.0f,
	.IMax = 0.0f,
	.SetPoint = 0.0f
};

extern rmc620_t chassis_motor[4];     

/**
  * @brief  底盘速度环参数初始化
  * @param  PID各参数
  * @retval None
  */
void chassis_vel_pid_init(float p, float i, float d, float i_max)
{
	int j = 0;
	
	for (j = 0; j < 4; j ++)
	{
		chassis_vel_pid[j].P = p;
		chassis_vel_pid[j].I = i;
		chassis_vel_pid[j].D = d;
        chassis_vel_pid[j].IMax = i_max;
		chassis_vel_pid[j].SetPoint = 0.0f;
	}
}

/**
  * @brief  底盘断电
  * @param  None
  * @retval None
  */
void chassis_power_off(void)
{
	chassis_current_send(0, 0, 0, 0);
}

/**
  * @brief  底盘速度分解及PID计算
  * @param  vx：左右速度
			vy：前后速度
			vw：旋转速度
  * @retval None
  */
int test_chassis_current[4];                 //only for debug to watch
void chassis_cal(int vx, int vy, int vw)
{
	int i = 0;
	
	chassis_vel_pid[0].SetPoint = LIMIT_MAX_MIN(-(vx + vy + vw), 10000, -10000);
	chassis_vel_pid[1].SetPoint = LIMIT_MAX_MIN((vx - vy - vw), 10000, -10000);
	chassis_vel_pid[2].SetPoint = LIMIT_MAX_MIN(-(-vx - vy + vw), 10000, -10000);
	chassis_vel_pid[3].SetPoint = LIMIT_MAX_MIN((-vx + vy - vw), 10000, -10000);
	
	for (i = 0; i < 4; i ++)
		test_chassis_current[i] = PID_Calc(&chassis_vel_pid[i], chassis_motor[i].speed);
	
	chassis_current_send(test_chassis_current[0], test_chassis_current[1], test_chassis_current[2], test_chassis_current[3]);
}

/**
  * @brief  底盘跟随陀螺仪YAW轴角度
  * @param  vx：左右速度
			vy：前后速度
			vw：旋转速度
  * @retval None
  */
void chassis_task(void)
{  
	if (g_flag.control_mode == RC_MODE)         //处于遥控模式，控制底盘及补弹气缸||g_flag.control_mode == LIFT_UP_MODE||g_flag.control_mode == SAVE_MODE
	{
		if (rc_ctrl.rc.ch0 > 1044 || rc_ctrl.rc.ch0 < 1004)
			vx = (1024 - rc_ctrl.rc.ch0) * 10.0f;
		else 
			vx = 0;
		
		if (rc_ctrl.rc.ch1 > 1044 || rc_ctrl.rc.ch1 < 1004)
			vy = (1024 - rc_ctrl.rc.ch1) * 10.0f;
		else 
			vy = 0;
		
		if (rc_ctrl.rc.ch2 > 1044 || rc_ctrl.rc.ch2 < 1004)
		{	
			if (g_flag.gyro_use_flag)	//使用陀螺仪数据
				chassis_pos_follow_pid.SetPoint += (1024 - rc_ctrl.rc.ch2) / 4000.0f;
			else						//不使用陀螺仪数据
				vw = (1024 - rc_ctrl.rc.ch2) * 10.0f;
		}
		else 
			vw = 0;
	}
	else if (g_flag.control_mode == POWER_OFF_MODE)         
	{
		chassis_power_off();
	}
	else if(g_flag.control_mode == LIFT_UP_MODE)
	{
		if(key_mode_use_chassis_flag == 1)
		{
				vx = (rc_ctrl.key.a - rc_ctrl.key.d) * (1.0F - rc_ctrl.key.shift * 0.85F+ rc_ctrl.mouse.press_l * 0.5F) * 2000.0F;
				vy = (-rc_ctrl.key.w + rc_ctrl.key.s) * (1.0F - rc_ctrl.key.shift * 0.85F+ rc_ctrl.mouse.press_l * 1.5F) * 2000.0F;
				if (g_flag.gyro_use_flag)	//使用陀螺仪数据
				{
					chassis_pos_follow_pid.SetPoint -= rc_ctrl.mouse.x / 300.0f * (1.0F - rc_ctrl.key.shift * 0.7F);    //键鼠
				}
				else						//不使用陀螺仪数据
					vw = -rc_ctrl.mouse.x * 100.0f * (1.0F - rc_ctrl.key.shift * 0.85F);
		  }
		else 
		{
					if (rc_ctrl.rc.ch0 > 1044 || rc_ctrl.rc.ch0 < 1004)
					vx = (1024 - rc_ctrl.rc.ch0) * 10.0f;
				else 
					vx = 0;
				
				if (rc_ctrl.rc.ch1 > 1044 || rc_ctrl.rc.ch1 < 1004)
					vy = (1024 - rc_ctrl.rc.ch1) * 10.0f;
				else 
					vy = 0;
				
				if (rc_ctrl.rc.ch2 > 1044 || rc_ctrl.rc.ch2 < 1004)
				{	
					if (g_flag.gyro_use_flag)	//使用陀螺仪数据
						chassis_pos_follow_pid.SetPoint += (1024 - rc_ctrl.rc.ch2) / 4000.0f;
					else						//不使用陀螺仪数据
						vw = (1024 - rc_ctrl.rc.ch2) * 10.0f;
				}
				else 
					vw = 0;

				
		}
	}
	if (ABS(vx - vx_set) > 100.0f && ((vx < -1000) || (vx > 1000)))             //启动时提速，停止时迅速刹车
		vx_set += 0.02f * (vx - vx_set);
	else
		vx_set = vx;
	
	if (ABS(vy - vy_set) > 100.0f && ((vy < -1000) || (vy > 1000)))             //启动时提速，停止时迅速刹车
		vy_set += 0.02f * (vy - vy_set);
	else
		vy_set = vy;
	
	if (g_flag.gyro_use_flag)
	{
			chassis_vel_follow_pid.SetPoint = LIMIT_MAX_MIN(PID_Calc(&chassis_pos_follow_pid, get_yaw_angle()), 5.7f, -5.7f);
			vw = PID_Calc(&chassis_vel_follow_pid, get_gz());
	}
	chassis_cal(vx_set, vy_set, vw);	
}
/**
  * @brief  底盘全向移动
  * @param  vx：左右速度
			vy：前后速度
			vw：旋转速度
  * @retval None
  */
void all_move(int vx1, int vy1)
{	
	if (g_flag.gyro_use_flag)       //使用陀螺仪，移动中保持方向不变
	{
		
		chassis_vel_follow_pid.SetPoint = LIMIT_MAX_MIN(PID_Calc(&chassis_pos_follow_pid, get_yaw_angle()), 5.7f, -5.7f);
		vw = PID_Calc(&chassis_vel_follow_pid, get_gz());
	}
	else
		vw = 0;
	chassis_cal(vx1, vy1, vw);
}

/**
  * @brief  附加旋转偏量
  * @param  speed：旋转速度
  * @retval None
  */						
void w_offset(float speed)
{
	if (w_offset_cnt < w_all_offset)
	{
		chassis_pos_follow_pid.SetPoint += speed;
		w_offset_cnt ++;
	}
	else if (w_offset_cnt > w_all_offset)
	{
		chassis_pos_follow_pid.SetPoint -= speed;
		w_offset_cnt --;
	}
	chassis_vel_follow_pid.SetPoint = LIMIT_MAX_MIN(PID_Calc(&chassis_pos_follow_pid, get_yaw_angle()), 5.7f, -5.7f);
		vw = PID_Calc(&chassis_vel_follow_pid, get_gz());
	chassis_cal(0, 0, vw);
}
void w_turn(float speed)
{
	chassis_pos_follow_pid.SetPoint -= speed;
	chassis_vel_follow_pid.SetPoint = LIMIT_MAX_MIN(PID_Calc(&chassis_pos_follow_pid, get_yaw_angle()), 5.7f, -5.7f);
		vw = PID_Calc(&chassis_vel_follow_pid, get_gz());
	//chassis_cal(0, 0, vw);
}

void  Chassis_task(void *pvParameters)
{
		while(1){
		
		chassis_task();
		
				vTaskDelay(2);
		#if INCLUDE_uxTaskGetStackHighWaterMark
        Chassis_high_water = uxTaskGetStackHighWaterMark(NULL);
#endif
    }
}
