#ifndef _TASKTOP_H
#define _TASKTOP_H
#include "stdint.h"
#include "TaskAction.h"
void Action_QR(void);  	//����1 ����һ��λ��ɨ��ά��
void Action_color(void);	//����2 ����ת��
void Grab_up(int mode,int put_angle,int put_pos,float y,float z);	//ץȡ����е������
void Grab_up_2(int mode,int put_angle,int put_pos,float y,float z);
void Action_rotate_grab(int mode);	//ת��ץȡ
void Put_ON_circle(int mode,int put_angle,int put_pos,float y,float z);	//Բ�����ã���е������
void circle_logic(uint8_t mode,const GM_PUTANGLE T);
void circle_logic_2(GM_PUTANGLE T);
void Action_WORK1(int mode);				//�����ӹ���
void Action_WORK2(int mode);		//���ﾫ�ӹ���
void Action_Back(void);		//�ص�������
#endif
