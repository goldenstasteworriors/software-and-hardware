#include "pwm.h"



/**************************************************************************
�������ܣ�pwm(TIM1)��ʼ��
��ڲ�����arr����Ϊһ��ʱ��Ƶ�ʵ����ֵ  psc�� Ԥ��Ƶֵ
����  ֵ����
**************************************************************************/
void PWM1_Int(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;                //����ṹ��GPIO_InitStructure
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;      //����ṹ��TIM_TimeBaseStructure   
	TIM_OCInitTypeDef TIM_OCInitStructure;              //����ṹ��TIM_OCInitStructure
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��PB�˿�ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//ʹ�ܶ�ʱ��3
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         //����ģʽ���
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10|GPIO_Pin_11; //PB0 ��PB1
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;        //IO���ٶ�
	GPIO_Init(GPIOA,&GPIO_InitStructure);                   //GPIO��ʼ��
	
	TIM_TimeBaseStructure.TIM_Period = arr;                //������һ�����»���Զ���װ�ؼĴ�����ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = psc;             //Ԥ����ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;           //ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode= TIM_OCMode_PWM1;             //PWM�����ȵ���1
	TIM_OCInitStructure.TIM_Pulse = 0;                           //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;    //����TIM�������Ϊ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ��
	TIM_OC3Init(TIM1,&TIM_OCInitStructure);
	TIM_OC4Init(TIM1,&TIM_OCInitStructure);
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);//�����ʹ��
	
	TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Enable);//ʹ��Ԥװ�ؼĴ���
	
	TIM_ARRPreloadConfig(TIM1,ENABLE);              //ʹ���Զ�װ������λ
	TIM_Cmd(TIM1,ENABLE);//������ʱ��3
	
	
}

/**************************************************************************
�������ܣ�pwm(TIM3)��ʼ��
��ڲ�����arr����Ϊһ��ʱ��Ƶ�ʵ����ֵ  psc�� Ԥ��Ƶֵ
����  ֵ����
**************************************************************************/
void PWM2_Int(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;                //����ṹ��GPIO_InitStructure
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;      //����ṹ��TIM_TimeBaseStructure   
	TIM_OCInitTypeDef TIM_OCInitStructure;              //����ṹ��TIM_OCInitStructure
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��PB�˿�ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//ʹ�ܶ�ʱ��3
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         //����ģʽ���
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1; //PB0 ��PB1
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;        //IO���ٶ�
	GPIO_Init(GPIOB,&GPIO_InitStructure);                   //GPIO��ʼ��
	
	TIM_TimeBaseStructure.TIM_Period = arr;                //������һ�����»���Զ���װ�ؼĴ�����ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = psc;             //Ԥ����ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;           //ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode= TIM_OCMode_PWM1;             //PWM�����ȵ���1
	TIM_OCInitStructure.TIM_Pulse = 0;                           //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;    //����TIM�������Ϊ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ��
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);
	TIM_OC4Init(TIM3,&TIM_OCInitStructure);
	
	TIM_CtrlPWMOutputs(TIM3,ENABLE);//�����ʹ��
	
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);//ʹ��Ԥװ�ؼĴ���
	
	TIM_ARRPreloadConfig(TIM3,ENABLE);              //ʹ���Զ�װ������λ
	TIM_Cmd(TIM3,ENABLE);//������ʱ��3
	
	
}

void Set_PWMA(int PWM)
{
   TIM_SetCompare3(TIM3,PWM);//����TIM3ͨ��3��ռ�ձ�  3000/7200
	
}
void Set_PWMB(int PWM)
{
   TIM_SetCompare4(TIM3,PWM);
	
}


void Set_PWMC(int PWM)
{
   TIM_SetCompare3(TIM1,PWM);//����TIM3ͨ��3��ռ�ձ�  3000/7200
	
}
void Set_PWMD(int PWM)
{
   TIM_SetCompare4(TIM1,PWM);
	
}
