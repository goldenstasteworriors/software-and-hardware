#ifndef _MYQUEUE_H
#define _MYQUEUE_H
#include "stdint.h"
#include "FreeRTOS.h"
#include "queue.h"

void queue_init(void);
//��������
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
	float pointY;			//y, z�������е������ƽ��
	float pointZ;
	
	int clip_angle;
	uint8_t time_delta[4];

} MecArmAttiSturcture;
typedef struct
{
	char target_oder1[3];			//��һȦ�Ķ�ά��˳��
	char target_oder2[3];			//�ڶ�Ȧ�Ķ�ά��˳��
	char real_oder[3];				//Բ�̵�˳��
}OderSturcture;

//����1 Բ���ĽǶȣ�����2 �۵ĽǶ�
typedef struct
{
	float circle_pos[3];				//Բ��������λ��
	float obj_pos[3];						//���������۵�λ��
	float y[3];
	float z[3];
}GM_PUTANGLE;
#endif
