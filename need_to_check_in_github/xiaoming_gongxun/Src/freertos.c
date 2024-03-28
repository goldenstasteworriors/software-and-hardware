/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "TaskMotor.h"
#include "TaskHMI.h"
#include "TaskCom.h"
#include "TaskAction.h"
#include "TaskMearm.h"
#include "TaskPir.h"
#include "TaskTop.h"
#include "TaskMotcor.h"
#include "myqueue.h"
#include "adc.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern QueueHandle_t ArmAttitudeQueueHandle;
extern QueueHandle_t bottom_moveHandle;
extern QueueHandle_t stratQueueHandle;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
extern int start_cmd;
uint8_t rx1;
/* USER CODE END Variables */
osThreadId HMITaskHandle;
osThreadId ComTaskHandle;
osThreadId TopTaskHandle;
osThreadId ActionTaskHandle;
osThreadId MearmTaskHandle;
osThreadId GM6020TaskHandle;
osThreadId PirTaskHandle;
osThreadId MotorTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void HMI_Task(void const * argument);
void Com_Task(void const * argument);
void Top_Task(void const * argument);
void Action_Task(void const * argument);
void Mearm_Task(void const * argument);
void GM6020_Task(void const * argument);
void Pir_Task(void const * argument);
void Motor_Task(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  queue_init(); 
	pid_para();
	mearm_init();
	GM_init();
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of HMITask */
  osThreadDef(HMITask, HMI_Task, osPriorityNormal, 0, 128);
  HMITaskHandle = osThreadCreate(osThread(HMITask), NULL);

  /* definition and creation of ComTask */
  osThreadDef(ComTask, Com_Task, osPriorityBelowNormal , 0, 128);
  ComTaskHandle = osThreadCreate(osThread(ComTask), NULL);

  /* definition and creation of TopTask */
  osThreadDef(TopTask, Top_Task, osPriorityBelowNormal, 0, 512);
  TopTaskHandle = osThreadCreate(osThread(TopTask), NULL);

  /* definition and creation of ActionTask */
  osThreadDef(ActionTask, Action_Task, osPriorityIdle, 0, 128);
  ActionTaskHandle = osThreadCreate(osThread(ActionTask), NULL);

  /* definition and creation of MearmTask */
  osThreadDef(MearmTask, Mearm_Task, osPriorityNormal, 0, 256);
  MearmTaskHandle = osThreadCreate(osThread(MearmTask), NULL);

  /* definition and creation of MotcorTask */
  osThreadDef(GM6020Task, GM6020_Task, osPriorityNormal, 0, 256);
  GM6020TaskHandle = osThreadCreate(osThread(GM6020Task), NULL);

  /* definition and creation of PirTask */
  osThreadDef(PirTask, Pir_Task, osPriorityIdle, 0, 128);
  PirTaskHandle = osThreadCreate(osThread(PirTask), NULL);

  /* definition and creation of MotorTask */
  osThreadDef(MotorTask, Motor_Task, osPriorityNormal, 0, 256);
  MotorTaskHandle = osThreadCreate(osThread(MotorTask), NULL);
 
  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_HMI_Task */
/**
  * @brief  Function implementing the HMITask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_HMI_Task */
void HMI_Task(void const * argument)
{
    

  /* USER CODE BEGIN HMI_Task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(100);
  }
  /* USER CODE END HMI_Task */
}

/* USER CODE BEGIN Header_Com_Task */
/**
* @brief Function implementing the ComTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Com_Task */
void Com_Task(void const * argument)
{
  /* USER CODE BEGIN Com_Task */
  /* Infinite loop */
//	char pWriteBuffer[2048];
  for(;;)
  {
//		vTaskList((char *)&pWriteBuffer);
//		printf("task_name   task_state  priority   stack  tasK_num\r\n");
//		printf("%s\n", pWriteBuffer);   
		osDelay(1000);
//	RUNNING_CHAR		( 'X' )
//	BLOCKED_CHAR		( 'B' )
//	READY_CHAR			( 'R' )
//	DELETED_CHAR		( 'D' )
//	SUSPENDED_CHAR	( 'S' )
  }
  /* USER CODE END Com_Task */
}

/* USER CODE BEGIN Header_Top_Task */
/**
* @brief Function implementing the TopTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Top_Task */
void Top_Task(void const * argument)
{
  /* USER CODE BEGIN Top_Task */
  /* Infinite loop */
			    
		init_pos();		
		GM_detect();
		vTaskDelay(800);
	
//-------------try code-------------begin//	
//
//const MecArmAttiSturcture scan_circle ={0,   270,    0.38,    0.09,    -4,     {0, 0, 0, 0}};		//É¨´ÖÔ²»·×ËÊÆ
//const MecArmAttiSturcture scan_cor ={0,   315,    0.28,    0.10,    -4,     {0, 0, 0, 0}};
//const MecArmAttiSturcture scan_circle2 ={0,   0,    0.30,    0.12,    -4,     {0, 0, 0, 0}};			//É¨Ï¸Ô²»·×ËÊÆ
//const MecArmAttiSturcture scan_cor_back ={0,   315,    0.24,    0.26,    -4,     {0, 0, 0, 0}};
//const MecArmAttiSturcture scan_circle2_2 ={ 0, 180 , 0.29,    0.15,    -4,     {0, 0, 0, 0}};			//É¨Ï¸Ô²»·×ËÊÆ
//MecArmAttiSturcture try1 ={1,   0,    0.08,    0.08,   -18,     {0, 0, 0, 0}};
//MecArmAttiSturcture try2 ={0,   300,    0.35,    0.08,    -18,     {0, 0, 0, 0}};
//MecArmAttiSturcture try3 ={0,   150,    0.35,    0.08,    -18,     {0, 0, 0, 0}};
//
// 		line_correct(270);
//		TASK_LIST();
//		Move_Servo(-0.5,0,0,0,0,0,0);
//		Mearm_Move(scan_circle2_2);
//		move_grap(180);
//		vTaskDelay(1000);
//		GM_kd(1);
//		circle_logic(0,s1_angle);
//		move_get_fang(0,0.30,-0.025);	
//		Grab_up(1,180,270,0.27,0.041);
//		move_to(0,550, 0);
//		Waitfinishmoving();
//		Mearm_Move(try3);		
//		vTaskDelay(1000);
//		Mearm_Move(try2);			
//		vTaskDelay(2000);
//		position_correct();	
//		
//-------------try code-------------end//	


//-------------run code-------------begin//	

//		while(1)
//		{
//			if(start_cmd==1)
//			{                    
//					vTaskDelay(2000);
//					break;           
//			}
//		}
//		start_cmd=2;
	if(xQueueReceive(stratQueueHandle, &rx1, portMAX_DELAY))
	{

		Action_QR();
		Action_color ();
		Action_rotate_grab(1);	

		move_to(0, 400 , 0);
		Waitfinishmoving();
		move_to(-930, 0, 0);
		Waitfinishmoving();
		Action_WORK1(1);
		
		move_to(-720, 0, 0);
		Waitfinishmoving();	
		move_to(0, -750, 0);
		
		Waitfinishmoving();
		
		Action_WORK2(1);
		Action_Back();	
		Action_rotate_grab(2);
		
		move_to(0, 400, 0);
		Waitfinishmoving();
		move_to(-930, 0, 0);
		Waitfinishmoving();
		
		Action_WORK1(2);		
				
		move_to(-700, 0, 0);
		Waitfinishmoving();	
		move_to(0, -765, 0);
		Waitfinishmoving();
		
		Action_WORK2(2);

		move_to(0, -920, 0);
		Waitfinishmoving();		
		line_correct(0);
		move_to(1730, 0, 0);
		Waitfinishmoving();	
		move_to(0, -100, 0);
}
//-------------run code-------------end//	

  for(;;)
  {	
//		Grab_up(1,180,270,0.27,0.041);
//		vTaskDelay(1000);
//		move_to(-700, 0, 0);
//		Waitfinishmoving();	
//		move_to(0, -765, 0);
//		Waitfinishmoving();
//		vTaskDelay(2000);
//		move_to(0, 600, 0);
//		vTaskDelay(2000);
//		Waitfinishmoving();
//		Action_QR();
//		Grab_up(1,180,270,0.27,0.041);
//		Action_rotate_grab();
//		printf("eodo \r\n");
//		Grab_up();
		
  }
  /* USER CODE END Top_Task */
}

/* USER CODE BEGIN Header_Action_Task */
/**
* @brief Function implementing the ActionTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Action_Task */
void Action_Task(void const * argument)
{
  /* USER CODE BEGIN Action_Task */
  /* Infinite loop */
  for(;;)
  {		
    osDelay(100);
  }
  /* USER CODE END Action_Task */
}

/* USER CODE BEGIN Header_Mearm_Task */
/**
* @brief Function implementing the MearmTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Mearm_Task */
void Mearm_Task(void const * argument)
{
  /* USER CODE BEGIN Mearm_Task */
//	MecArmAttiSturcture  rx;
  /* Infinite loop */
	
  for(;;)
  {
		Task_Mearm();
    osDelay(10);
  }
  /* USER CODE END Mearm_Task */
}

/* USER CODE BEGIN Header_Motcor_Task */
/**
* @brief Function implementing the MotcorTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Motcor_Task */
void GM6020_Task(void const * argument)
{
  /* USER CODE BEGIN Motcor_Task */
  /* Infinite loop */
  for(;;)
  {
		rm_servo();	
    osDelay(20);
  }
  /* USER CODE END Motcor_Task */
}

/* USER CODE BEGIN Header_Pir_Task */
/**
* @brief Function implementing the PirTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Pir_Task */
void Pir_Task(void const * argument)
{
  /* USER CODE BEGIN Pir_Task */

	/* Infinite loop */
  for(;;)
  {
    osDelay(100);

  }
  /* USER CODE END Pir_Task */
}

/* USER CODE BEGIN Header_Motor_Task */
/**
* @brief Function implementing the MotorTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Motor_Task */
void Motor_Task(void const * argument)
{
  /* USER CODE BEGIN Motor_Task */

	
	
  /* Infinite loop */
  for(;;)
  {
		Task_Motor();
    osDelay(10);
		
  }
  /* USER CODE END Motor_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
