#include "TaskAction.h"
//#include "myqueue.h"
//����λ����Ϣ
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
//ִ�в���
void Task_action()
{
	
}
