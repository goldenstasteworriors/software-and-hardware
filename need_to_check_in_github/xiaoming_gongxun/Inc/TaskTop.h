#ifndef _TASKTOP_H
#define _TASKTOP_H
#include "stdint.h"
#include "TaskAction.h"
void Action_QR(void);  	//任务1 到第一个位置扫二维码
void Action_color(void);	//任务2 到达转盘
void Grab_up(int mode,int put_angle,int put_pos,float y,float z);	//抓取，机械臂流程
void Grab_up_2(int mode,int put_angle,int put_pos,float y,float z);
void Action_rotate_grab(int mode);	//转盘抓取
void Put_ON_circle(int mode,int put_angle,int put_pos,float y,float z);	//圆环放置，机械臂流程
void circle_logic(uint8_t mode,const GM_PUTANGLE T);
void circle_logic_2(GM_PUTANGLE T);
void Action_WORK1(int mode);				//到达半加工区
void Action_WORK2(int mode);		//到达精加工区
void Action_Back(void);		//回到出发点
#endif
