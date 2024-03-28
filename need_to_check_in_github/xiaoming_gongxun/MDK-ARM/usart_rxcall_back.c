#include "usart_rxcall_back.h"
#include "stdio.h"
#include "main.h"
#include "stm32f4xx_it.h"
#include "FreeRTOS.h"
#include "TaskCom.h"
#include "myqueue.h"
#include "TaskHMI.h"
//HAL库的串口通信
/*①在main里开启第一次接收中断,定义接收缓冲区为数组(n个字节)
②在自带文件stm32f4xx.it.c, 的串口中断处理函数开启接收中断(n个字节)
③编写接收回调函数，再次开启接收中断(n个字节)
④重定向printf
*/
//中断处理函数处理数据，中断回调函数执行程序
extern uint8_t Res[8];
extern uint8_t buf1[256];
extern UART_HandleTypeDef huart2,huart6;
extern QueueHandle_t RasperryQRQueueHandle,RasperryitemQueueHandle;
extern QueueHandle_t WORK1QueueHandle,WORK2QueueHandle;
extern QueueHandle_t stratQueueHandle;
uint8_t rx = 1;
uint8_t head;
float Xoffset,Yoffset,Zoffset;
int Xpositon,Ypositon;
OderSturcture rx_oder;
int start_cmd;
extern uint8_t res_hmi;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{ 
		
	head = Res[0];
	if(huart->Instance==USART2)
	{	
	portYIELD_FROM_ISR(pdFALSE);
		if(head == 'a')			//抓取顺序
		{	
			uint8_t rasp_QRdata=1;			//发送缓冲区
			for(int i =0; i<3; i++)
			{
				rx_oder.target_oder1[i] = Res[i+1];			//第一轮抓取，放置顺序
				rx_oder.target_oder2[i] = Res[i+5];
				xQueueSendFromISR(RasperryQRQueueHandle,(uint8_t *)rasp_QRdata,pdFALSE);	//在中断中发消息
//				printf("%c",rx_oder.target_oder1[i]);
			}
			int send1 = ((Res[1]-'0')*100+(Res[2]-'0')*10+(Res[3]-'0'));
			int send2 = ((Res[5]-'0')*100+(Res[6]-'0')*10+(Res[7]-'0'));
//			sprintf((char *)buf1,"page2.t0.txt=\"213+333\"");	//print
			sprintf((char *)buf1,"page1.t0.txt=\"%d+%d\"",send1,send2);	//print
			HMISends((uint8_t *)buf1);
			HMISendb(0xff);
		}
		if(head =='b')				//颜色顺序
		{
			uint8_t rasp_colordata;
//			uint8_t cmd = '2';
//			uint8_t ref_order[3];
				for(int i =0; i<3; i++)
			{				
			rx_oder.real_oder[i] = Res[i+1];
//			ref_order[i] = rx_oder.real_oder[i];
			}
//			while(1)
//			{
//					HAL_UART_Transmit(&huart2,&cmd,sizeof(cmd),100000);
//					for(int i =0; i<3; i++)
//					{				
//						rx_oder.real_oder[i] = Res[i+1];
//					}
//					if(strcmp(rx_oder.real_oder,ref_order)!=0)
//					{
//							xQueueSendFromISR(RasperryitemQueueHandle,&rasp_colordata,pdFALSE);
//							break;
//					}
//						for(int i =0; i<3; i++)
//					{		
//						ref_order[i] =  rx_oder.real_oder[i];
//					}
//								
//			}
		}
		
		if(head == 'c'||head == 'h')		
		{
			uint8_t x_offset[3];
			uint8_t y_offset[3];
			for(int i =0 ; i<3 ;i++)
			{
				x_offset[i] = Res[i+1];
				y_offset[i] = Res[i+5];
			}
			
				if((x_offset[0]-'0')>0)
			{
				Xoffset = -((x_offset[1]-'0')*10+(x_offset[2]-'0'));
			}
			else
			{
				Xoffset = ((x_offset[1]-'0')*10+(x_offset[2]-'0'));
			}
			if((y_offset[0]-'0')>0)
			{
				Yoffset = -((y_offset[1]-'0')*10+(y_offset[2]-'0'));
			}
			else
			{
				Yoffset = ((y_offset[1]-'0')*10+(y_offset[2]-'0'));
			}
		}
		
		if(head == 'd')			
		{
			uint8_t z_offset[5];
			for(int i =0 ; i<5 ;i++)
			{
				z_offset[i] = Res[i+1];
			}
			
				if((z_offset[0]-'0')>0)
			{
				Zoffset = -((z_offset[1]-'0')*10+(z_offset[2]-'0')+(z_offset[3]-'0')*0.1+(z_offset[4]-'0')*0.01);
			}
			else
			{
				Zoffset = ((z_offset[1]-'0')*10+(z_offset[2]-'0')+(z_offset[3]-'0')*0.1+(z_offset[4]-'0')*0.01);			
			}
		}
		
		if(head == 'e')			//角点检测
		{
			uint8_t x_position[3];
			uint8_t y_position[3];
			for(int i =0 ; i<3 ;i++)
			{
				x_position[i] = Res[i+1];
				y_position[i] = Res[i+5];
			}
			if((x_position[0]-'0')>0)
			{
				Xpositon = -((x_position[1]-'0')*10+(x_position[2]-'0'));
			}
			else
			{
				Xpositon = ((x_position[1]-'0')*10+(x_position[2]-'0'));
				
			}
			if((y_position[0]-'0')>0)
			{
				
				Ypositon = -((y_position[1]-'0')*10+(y_position[2]-'0'));
			}
			else
			{
				Ypositon = ((y_position[1]-'0')*10+(y_position[2]-'0'));
			}
		}
		
		if(head == 'f')
		{
//			uint8_t rx_move = '1';
//			xQueueSendFromISR(WORK1QueueHandle,&rx_move,pdFALSE);
		}
		
		
//		uint8_t i=0;
//		while(1)
//		{
//		 if(Res[i]!=0)
//			{					
//				HAL_UART_Transmit(&huart2,&Res[i],sizeof(Res[i]),100000);   //发送不定长数据
//				while(HAL_UART_GetState(&huart2)==RESET){};//等待发送结束
//				i++;
//			}
//		 else 
//		 return ;

//		}
		HAL_UART_Receive_IT(&huart2,Res,8);
	}
		if(huart->Instance==USART6)
	{
		
		if(res_hmi == 'g')
		xQueueSendFromISR(stratQueueHandle,(uint8_t *)rx,pdFALSE);
			start_cmd =1;
		HAL_UART_Receive_IT(&huart6,&res_hmi,1);
	}		

}
