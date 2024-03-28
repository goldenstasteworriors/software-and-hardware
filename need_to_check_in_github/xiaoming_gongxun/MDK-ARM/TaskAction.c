#include "TaskAction.h"
//#include "myqueue.h"
//发送位置消息
extern QueueHandle_t bottom_moveHandle;
extern QueueHandle_t ArmAttitudeQueueHandle;
POSITON pos[8];

void move_to(float x , float y , float angle)
{
	pos[0].x = x;
	pos[0].y = y;
	pos[0].angle = angle;
	xQueueSendToBack(bottom_moveHandle, &pos[0], 0);
	
}

void Mearm_Move(const MecArmAttiSturcture S)
{
	xQueueSendToBack(ArmAttitudeQueueHandle, &S, 0);
}
//执行部分
void Task_action()
{
	
}
