#include "main.h" 
#include "FreeRTOS.h"
#include "task.h"

#include "start_task.h" 
#include "delay.h"
#include "tim.h"

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
	
	TIM2_Init();
	TIM3_Init();
	TIM4_Init();
}
