#include "gpio.h"

void Gpio_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;            //����ṹ��GPIO_InitStructure
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE); // ʹ��PB�˿�ʱ��  
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_12| GPIO_Pin_13;	  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     	//���죬��������������  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //IO���ٶ�
	GPIO_Init(GPIOB, &GPIO_InitStructure);          //GBIOB��ʼ��  
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_13|GPIO_Pin_14; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     	//���죬��������������  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //IO���ٶ�
	GPIO_Init(GPIOC, &GPIO_InitStructure);          //GBIOB��ʼ��  
 
}
 
