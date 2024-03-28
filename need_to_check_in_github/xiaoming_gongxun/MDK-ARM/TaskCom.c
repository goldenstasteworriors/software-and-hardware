#include "TaskCom.h"
#include "FreeRTOS.h"
#include <stdio.h>
#include <stdint.h>
#include <usart.h>
#include "task.h"

void TASK_LIST(void)
{
    char pWriteBuffer[2048];
    for(int i=0;i<1;i++)
    {
        vTaskList((char *)&pWriteBuffer);
        printf("task_name   task_state  priority   stack  tasK_num\r\n");
        printf("%s\n", pWriteBuffer);   
    }
    vTaskDelete(NULL);
}


void Task_com()
{

}
