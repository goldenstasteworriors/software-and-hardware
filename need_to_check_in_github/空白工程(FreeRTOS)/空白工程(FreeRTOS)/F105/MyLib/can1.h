#ifndef _CAN1_H_
#define _CAN1_H_

void CAN1_Config(void);
void chassis_current_send(int a, int b, int c, int d);
void track_current_send(int left, int right);

#endif
