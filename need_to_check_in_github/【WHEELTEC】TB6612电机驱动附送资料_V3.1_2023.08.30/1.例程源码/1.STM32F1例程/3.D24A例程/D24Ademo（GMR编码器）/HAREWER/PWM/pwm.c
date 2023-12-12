#include "pwm.h"



/**************************************************************************
�������ܣ�pwm��ʼ��
��ڲ�����arr����Ϊһ��ʱ��Ƶ�ʵ����ֵ  psc�� Ԥ��Ƶֵ
����  ֵ����
**************************************************************************/
void PWM_Int(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;                //����ṹ��GPIO_InitStructure
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;      //����ṹ��TIM_TimeBaseStructure   
	TIM_OCInitTypeDef TIM_OCInitStructure;              //����ṹ��TIM_OCInitStructure
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PA�˿�ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);//ʹ�ܶ�ʱ��3
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = arr;                //������һ�����»���Զ���װ�ؼĴ�����ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = psc;             //Ԥ����ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;           //ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode= TIM_OCMode_PWM1;             //PWM�����ȵ���1
	TIM_OCInitStructure.TIM_Pulse = 0;                           //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;    //����TIM�������Ϊ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ��
	TIM_OC1Init(TIM5,&TIM_OCInitStructure);
	TIM_OC2Init(TIM5,&TIM_OCInitStructure);
	TIM_OC3Init(TIM5,&TIM_OCInitStructure);
	TIM_OC4Init(TIM5,&TIM_OCInitStructure);
	
	
	TIM_OC1PreloadConfig(TIM5,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM5,TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM5,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM5,TIM_OCPreload_Enable);//ʹ��Ԥװ�ؼĴ���
	
	TIM_ARRPreloadConfig(TIM5,ENABLE);              //ʹ���Զ�װ������λ
	TIM_Cmd(TIM5,ENABLE);//������ʱ��5	
}

void Set_PWM(int motor1,int motor2,int motor3,int motor4)
{
	TIM_SetCompare1(TIM5,motor1);
	TIM_SetCompare2(TIM5,motor2);
    TIM_SetCompare3(TIM5,motor3);//����TIM3ͨ��3��ռ�ձ�  3000/7200
    TIM_SetCompare4(TIM5,motor4);
	
}



