#include "stm32f10x.h"

#include "delay.h"
#include "gpio.h"
#include "moto.h"
#include "pwm.h"
#include "adc.h"
#include "usart.h"
#include "encoder.h"

 /**************************************************************************
公司：轮趣科技(东莞)有限公司
品牌：WHEELTEC
官网：wheeltec.net
淘宝店铺：shop114407458.taobao.com 
速卖通: https://minibalance.aliexpress.com/store/4455017
版本：V1.0
修改时间：2022-09-01

Brand: WHEELTEC
Website: wheeltec.net
Taobao shop: shop114407458.taobao.com 
Aliexpress: https://minibalance.aliexpress.com/store/4455017
Version: V1.0
Update：2023-06-28

All rights reserved
**************************************************************************/



 
int TargetVelocity=15000;
int main(void)
 {	
	 int encoder_A,encoder_B,encoder_C,encoder_D;
	 int Velocity_PWMA=0,Velocity_PWMB=0,Velocity_PWMC=0,Velocity_PWMD=0;
	 u16 adcx;
	 float vcc;
   SystemInit(); //配置系统时钟为72M   
   delay_init();    //延时函数初始化
   Gpio_Init();    //初始化gpioB pin_0/1/8/9/12/13/14/15
   uart_init(115200);		//串口初始化
	 
   adc_Init();				//ADC1的初始化 
	 
   PWM_Int(7199,0);      //初始化pwm输出 72000 000 /7199+1=10000    
   Encoder_Init_Tim8();
   Encoder_Init_Tim2();
   Encoder_Init_Tim3();
   Encoder_Init_Tim4();
  while(1)
	{
	    moto(0);                //moto=0时逆时针转动
//	    moto(1);                //moto=1时顺势正转动

		adcx=Get_adc_Average(ADC_Channel_5,10);  //获取adc的值
		vcc=(float)adcx*(3.3*11/4096);     				//求当前电压
		encoder_A=Read_Encoder(8);		//读取编码器数值
		encoder_B=Read_Encoder(2);
		encoder_C=Read_Encoder(3);
		encoder_D=Read_Encoder(4);
    	Velocity_PWMA=Velocity_A(TargetVelocity,encoder_A);
		Velocity_PWMB=Velocity_B(TargetVelocity,encoder_B);
		Velocity_PWMC=Velocity_C(TargetVelocity,encoder_C);
		Velocity_PWMD=Velocity_D(TargetVelocity,encoder_D);
		Set_PWM(Velocity_PWMA,Velocity_PWMB,Velocity_PWMC,Velocity_PWMD);
		printf("当前电压=%6.2f V  Encoder_A = %d  Encoder_B=%d\r\n   Encoder_C = %d  Encoder_D=%d\r\n",vcc,encoder_A,Velocity_PWMA,encoder_C,encoder_D);				//打印当前电压，保留小数点后两位	
	}
 }

