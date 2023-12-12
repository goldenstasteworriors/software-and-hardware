#include "Start_Task.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "tim.h"

uint32_t CPU_high_water;

#define START_TASK_PRIO 1  //�������ȼ�
#define START_STK_SIZE 512 //�����ջ
static TaskHandle_t StartTask_Handler; //������

#define CPU_TASK_PRIO 20  //�������ȼ�
#define CPU_STK_SIZE 512 //�����ջ
static TaskHandle_t CPUTask_Handler; //������

void start_task(void *pvParameters)
{
  taskENTER_CRITICAL();
	
	xTaskCreate((TaskFunction_t)CPU_task,          //������
                (const char *)"CPU_task",          //��������
                (uint16_t)CPU_STK_SIZE,            //�����ջ��С
                (void *)NULL,                        //���ݸ��������Ĳ���
                (UBaseType_t)CPU_TASK_PRIO,        //�������ȼ�
                (TaskHandle_t *)&CPUTask_Handler); //������
	
	vTaskDelete(StartTask_Handler); //ɾ����ʼ����
  taskEXIT_CRITICAL();            //�˳��ٽ���
}



void CPU_task(void *pvParameters)
{
	
	uint8_t CPU_RunInfo1[200]; //������������ʱ����Ϣ �ֱ��ǣ������� ����״̬ ���ȼ� ʣ��ջ �������
  uint8_t CPU_RunInfo2[200]; //������������ʱ����Ϣ �ֱ��ǣ������� ���м���  ʹ����
	
   while (1) {
    memset(CPU_RunInfo1,0,200); //��Ϣ����������
 
    vTaskList((char *)&CPU_RunInfo1); //��ȡ��������ʱ����Ϣ
    
    memset(CPU_RunInfo2,0,200); //��Ϣ����������
 
    vTaskGetRunTimeStats((char *)&CPU_RunInfo2);
    vTaskDelay(1000); /* ��ʱ 500 �� tick */
		 
#if INCLUDE_uxTaskGetStackHighWaterMark
        CPU_high_water = uxTaskGetStackHighWaterMark(NULL);
#endif
    }
}
void startTast(void)
{
    xTaskCreate((TaskFunction_t)start_task,          //������
                (const char *)"start_task",          //��������
                (uint16_t)START_STK_SIZE,            //�����ջ��С
                (void *)NULL,                        //���ݸ��������Ĳ���
                (UBaseType_t)START_TASK_PRIO,        //�������ȼ�
                (TaskHandle_t *)&StartTask_Handler); //������
}

