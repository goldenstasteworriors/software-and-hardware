#include "stm32f10x.h"
#include "delay.h"
#include "gpio.h"
#include "moto.h"
#include "pwm.h"
#include "adc.h"
#include "usart.h"
#include "encoder.h"


 /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/

int TargetVelocity=500;
float Velcity_Kp=0.2,  Velcity_Ki=0.1,  Velcity_Kd; //相关速度PID参数

int main(void)
 {	 
	 int encoder_A,encoder_B;
	 int Velocity_PWM1=0,Velocity_PWM2=0;
	 u16 adcx;
	 float vcc;                                         
   SystemInit(); //配置系统时钟为72M   
   delay_init();    //延时函数初始化
   Gpio_Init();    //初始化gpio口B pin_12/pin_13/14/15
   uart_init(9600);		//串口初始化
	 
   adc_Init();				//ADC1的初始化   只有TB6612带稳压模块版才有获取电池电压的功能，只有TB6612FNG没有这个功能
	 
   PWM_Int(7199,0);      //初始化pwm输出 72000 000 /7199+1=10000 
   Encoder_Init_Tim2();
   Encoder_Init_Tim4();
  while(1)
	{
//   moto(0);                //moto=0时正转
//	    moto(1);                //moto=1时反转

		adcx=Get_adc_Average(ADC_Channel_6,10);  //获取adc的值
		vcc=(float)adcx*(3.3*11/4096);     				//求当前电压
	
		encoder_B=-Read_Encoder(2);		//读取编码器数值
    encoder_A=-Read_Encoder(4); 	
		Velocity_PWM2=Velocity_A(TargetVelocity,encoder_A);
		Velocity_PWM1=Velocity_B(TargetVelocity,encoder_B);

		Set_PWMA(Velocity_PWM1);
	  Set_PWMB(Velocity_PWM2);
		printf("当前电压=%6.2f V  Encoder_A = %d  Encoder_B=%d\r\n",vcc,encoder_A,encoder_B);				//打印当前电压，保留小数点后两位	
	 }
 }
   
