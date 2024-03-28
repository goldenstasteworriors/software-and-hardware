#ifndef _TASKMOTCOR_H
#define _TASKMOTCOR_H
#include "stdint.h"
#include "spi.h"
#include "bsp_can.h"
#include "pid.h"
#include "Remote_Control.h"
#include "bsp_imu.h"
#include <stdio.h>    //��׼�����⺯����Printf��������
#include "string.h"   //��׼�⺯�����ַ�������
#include "ctype.h"    //��׼�⺯�����ַ�����
#include "stm32f4xx_it.h"
#include "Mecanum.h"

//void Goto(float x, float y, float angle);
void GotoY(float y);
void GotoX(float x);
void GotoXY(float x,float y);
void GotoXYZ(float x,float y,float angle);
void correct2(void);
void correct_xyz(float x,float y,float z);
void GetYaw(void);
void position_correct(void);
void round_correct(void);
void round_correct2(int mode);
void GotoZ(float z);
void line_correct(int angle);
void pid_para(void);
void Task_Motor(void);
void Waitfinishmoving(void);
#endif
