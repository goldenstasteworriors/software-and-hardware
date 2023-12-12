#ifndef _CAN2_H_
#define _CAN2_H_

void CAN2_Config(void);
float get_yaw_angle(void);
float get_gz(void);
void can2_move_send(int a);
void can2_lateral_send(int a);

#endif

