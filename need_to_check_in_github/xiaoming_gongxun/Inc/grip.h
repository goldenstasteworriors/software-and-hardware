#ifndef _GRIP_H
#define _GRIP_H
#include "stdint.h"

void rm_servo(double angle);		//��̨�����
//void servo1(float angle);
//void servo2(float angle);
//void servo3(float angle);
void clip(double angle);			//���Ӷ��

//��е�۵Ĳ�ͬ��̬
void init_pos();
void move_get();
void move_put();
void move_turn();
void move_get2();
void up();
typedef struct
{
  float pointX;		//y, z�������е������ƽ��
	float pointY;		//x, y�������̨����ƽ��
	float pointZ;
	uint8_t mode;
	int clip_angle;
	uint8_t time_delta[4];
	//float handBiasAngle;				//��3��x��ĸ�����
	//uint8_t mode;	//	1 normal
	//float panAngle;
} MecArmAttiSturcture;
uint8_t attitudeGetAngle_get(const MecArmAttiSturcture S, float *pTheta);
uint8_t attitudeGetAngle_put(const MecArmAttiSturcture S, float *ptheta);
uint8_t Move_Servo(float servo1_angle,float servo2_angle,float servo3_angle,float servo4_angle,uint32_t time1,uint32_t time2,uint32_t time3,uint32_t time4);
extern float servoAngle[5];
extern float servoRefAngle[4];
#endif
