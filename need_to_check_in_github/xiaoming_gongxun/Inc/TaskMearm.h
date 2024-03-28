#ifndef _TASKMEARM_H
#define _TASKMEARM_H
#include "stdint.h"
#include "myqueue.h"
void rm_servo(void);		//云台舵机角

void clip(double angle);			//夹子舵机

//机械臂的不同姿态
//抓
void init_pos(void);
void zhua_detect(void);
void shou(int angle);
void move_turn_grab(int put_pos);
void move_turn_put(int put_pos);
void move_turn_song(int put_pos);
void move_get_zhua(int put_angle,float y, float z);
void move_get_zhua2(int put_angle,float y, float z);
void move_get_fang(int put_angle,float y, float z);
void up_grab(int put_angle,float y);
void move_put(int put_pos);
void move_put_up(int put_pos);
void move_grap_up0(int put_pos);
void move_grap(int put_pos);
void move_grap_up(int put_pos);
void GM_kd(int mode);

uint8_t attitudeGetAngle_get(const MecArmAttiSturcture S, float *pTheta);
uint8_t attitudeGetAngle_put(const MecArmAttiSturcture S, float *ptheta);
void Move_Servo(float servo1_angle,float servo2_angle,float servo3_angle,uint32_t time1,uint32_t time2,uint32_t time3,uint32_t time4);
extern float servoAngle[5];
extern float servoRefAngle[4];

void Task_Mearm(void);//执行部分
void mearm_init(void);
void GM_init(void);
void GM_detect(void);
void try1(void);
void back_grab(int put_angle,float y, float z);
void back_grab_2(int put_angle,float y, float z);
void mearm_y(MecArmAttiSturcture S,float y);
void mearm_z(MecArmAttiSturcture S,float z);
#endif
