#include "pwm.h"



/**************************************************************************
函数功能：pwm(TIM1)初始化
入口参数：arr：设为一个时钟频率的最大值  psc： 预分频值
返回  值：无
**************************************************************************/
void PWM1_Int(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;                //定义结构体GPIO_InitStructure
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;      //定义结构体TIM_TimeBaseStructure   
	TIM_OCInitTypeDef TIM_OCInitStructure;              //定义结构体TIM_OCInitStructure
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PB端口时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//使能定时器3
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         //复用模式输出
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10|GPIO_Pin_11; //PB0 、PB1
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;        //IO口速度
	GPIO_Init(GPIOA,&GPIO_InitStructure);                   //GPIO初始化
	
	TIM_TimeBaseStructure.TIM_Period = arr;                //设置下一个更新活动的自动重装载寄存器的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc;             //预分配值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;           //时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode= TIM_OCMode_PWM1;             //PWM脉冲宽度调制1
	TIM_OCInitStructure.TIM_Pulse = 0;                           //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;    //设置TIM输出极性为高
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
	TIM_OC3Init(TIM1,&TIM_OCInitStructure);
	TIM_OC4Init(TIM1,&TIM_OCInitStructure);
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);//主输出使能
	
	TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Enable);//使能预装载寄存器
	
	TIM_ARRPreloadConfig(TIM1,ENABLE);              //使能自动装载允许位
	TIM_Cmd(TIM1,ENABLE);//启动定时器3
	
	
}

/**************************************************************************
函数功能：pwm(TIM3)初始化
入口参数：arr：设为一个时钟频率的最大值  psc： 预分频值
返回  值：无
**************************************************************************/
void PWM2_Int(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;                //定义结构体GPIO_InitStructure
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;      //定义结构体TIM_TimeBaseStructure   
	TIM_OCInitTypeDef TIM_OCInitStructure;              //定义结构体TIM_OCInitStructure
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PB端口时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//使能定时器3
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         //复用模式输出
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1; //PB0 、PB1
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;        //IO口速度
	GPIO_Init(GPIOB,&GPIO_InitStructure);                   //GPIO初始化
	
	TIM_TimeBaseStructure.TIM_Period = arr;                //设置下一个更新活动的自动重装载寄存器的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc;             //预分配值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;           //时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode= TIM_OCMode_PWM1;             //PWM脉冲宽度调制1
	TIM_OCInitStructure.TIM_Pulse = 0;                           //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;    //设置TIM输出极性为高
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);
	TIM_OC4Init(TIM3,&TIM_OCInitStructure);
	
	TIM_CtrlPWMOutputs(TIM3,ENABLE);//主输出使能
	
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);//使能预装载寄存器
	
	TIM_ARRPreloadConfig(TIM3,ENABLE);              //使能自动装载允许位
	TIM_Cmd(TIM3,ENABLE);//启动定时器3
	
	
}

void Set_PWMA(int PWM)
{
   TIM_SetCompare3(TIM3,PWM);//设置TIM3通道3的占空比  3000/7200
	
}
void Set_PWMB(int PWM)
{
   TIM_SetCompare4(TIM3,PWM);
	
}


void Set_PWMC(int PWM)
{
   TIM_SetCompare3(TIM1,PWM);//设置TIM3通道3的占空比  3000/7200
	
}
void Set_PWMD(int PWM)
{
   TIM_SetCompare4(TIM1,PWM);
	
}
