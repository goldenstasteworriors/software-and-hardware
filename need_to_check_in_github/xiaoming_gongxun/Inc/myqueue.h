#ifndef _MYQUEUE_H
#define _MYQUEUE_H
#include "stdint.h"
#include "FreeRTOS.h"
#include "queue.h"

void queue_init(void);
//底盘坐标
typedef struct
{
	float x;
	float y;
	float angle;
}POSITON;

typedef struct
{
	uint8_t mode;
  int GM_angle;		
	float pointY;			//y, z面决定机械臂所在平面
	float pointZ;
	
	int clip_angle;
	uint8_t time_delta[4];

} MecArmAttiSturcture;
typedef struct
{
	char target_oder1[3];			//第一圈的二维码顺序
	char target_oder2[3];			//第二圈的二维码顺序
	char real_oder[3];				//圆盘的顺序
}OderSturcture;

//参数1 圆环的角度，参数2 槽的角度
typedef struct
{
	float circle_pos[3];				//圆环的三个位置
	float obj_pos[3];						//车上三个槽的位置
	float y[3];
	float z[3];
}GM_PUTANGLE;
#endif
