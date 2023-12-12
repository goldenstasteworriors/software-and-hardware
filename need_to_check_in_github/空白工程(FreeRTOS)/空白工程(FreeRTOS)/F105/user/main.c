#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

#include "start_task.h"
#include "can1.h"
#include "can2.h"
#include "led.h"
#include "usart.h"
#include "pid.h"
#include "delay.h"
#include "remote.h"
#include "state_task.h"
#include "chassis_task.h"
#include "tim.h"


flag_t g_flag;

void BSP_init(void);

int main(void)
{
   BSP_init();
   delay_ms(100);
	 startTast();
   vTaskStartScheduler();
   while (1)
   {
        ;
   }
}





void BSP_init(void)
{
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
	
	LED_Config();
	CAN1_Config();
	CAN2_Config();
	
  chassis_vel_pid_init(7.5f, 2.5f, 10.0f, 100.0f);
	
	TIM4_Init();
	TIM6_Configration();
	TIM7_Configration();
}
