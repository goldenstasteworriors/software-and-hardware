#include "stm32f10x.h"
#include "delay.h"
#include "gpio.h"
#include "moto.h"
#include "pwm.h"
#include "adc.h"
#include "usart.h"
#include "encoder.h"


 /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/

int TargetVelocity=500;
float Velcity_Kp=0.2,  Velcity_Ki=0.1,  Velcity_Kd; //����ٶ�PID����
int encoder_A,encoder_B,encoder_C,encoder_D;
int Velocity_PWM1=0,Velocity_PWM2=0,Velocity_PWM3=0,Velocity_PWM4=0;
u16 adcx,adcy;
float vcc;
void control_and_report(void);

int main(void)
 {	 
                                         
   SystemInit(); //����ϵͳʱ��Ϊ72M   
   delay_init();    //��ʱ������ʼ��
   Gpio_Init();    //��ʼ��gpio��B pin_12/pin_13/14/15
   uart_init(9600);		//���ڳ�ʼ��
	 
   adc1_Init();				//ADC1�ĳ�ʼ��   ֻ��TB6612����ѹģ�����л�ȡ��ص�ѹ�Ĺ��ܣ�ֻ��TB6612FNGû���������
	 adc2_Init();				//ADC1�ĳ�ʼ��   ֻ��TB6612����ѹģ�����л�ȡ��ص�ѹ�Ĺ��ܣ�ֻ��TB6612FNGû���������
	 
   PWM1_Int(7199,0);      //��ʼ��pwm��� 72000 000 /7199+1=10000 
   PWM2_Int(7199,0);      //��ʼ��pwm��� 72000 000 /7199+1=10000	 
   Encoder_Init_Tim1();
	 Encoder_Init_Tim2();
   Encoder_Init_Tim3();
   Encoder_Init_Tim4();
  while(1)
	{
//   moto1(0);                //moto=0ʱ��ת
//	    moto1(1);                //moto=1ʱ��ת
//   moto2(0);                //moto=0ʱ��ת
//	    moto2(1);                //moto=1ʱ��ת
		control_and_report();

	 }
 }
 
 
 
void control_and_report(void)
{
		adcx=Get_adc1_Average(ADC_Channel_6,10);  //��ȡadc��ֵ
		vcc=(float)adcx*(3.3*11/4096);     				//��ǰ��ѹ
	
		encoder_B=-Read_Encoder(2);		//��ȡ��������ֵ
    encoder_A=-Read_Encoder(4); 	
		Velocity_PWM2=Velocity_A(TargetVelocity,encoder_A);
		Velocity_PWM1=Velocity_B(TargetVelocity,encoder_B);

		Set_PWMA(Velocity_PWM1);
	  Set_PWMB(Velocity_PWM2);
		printf("��1��ǰ��ѹ=%6.2f V  Encoder_A = %d  Encoder_B=%d\r\n",vcc,encoder_A,encoder_B);				//��ӡ��ǰ��ѹ������С�������λ	
		
		adcy=Get_adc2_Average(ADC_Channel_6,10);  //��ȡadc��ֵ
		vcc=(float)adcy*(3.3*11/4096);     				//��ǰ��ѹ
	
		encoder_D=-Read_Encoder(3);		//��ȡ��������ֵ
    encoder_C=-Read_Encoder(1); 	
		Velocity_PWM3=Velocity_C(TargetVelocity,encoder_C);
		Velocity_PWM4=Velocity_D(TargetVelocity,encoder_D);

		Set_PWMC(Velocity_PWM3);
	  Set_PWMD(Velocity_PWM4);
		printf("��2��ǰ��ѹ=%6.2f V  Encoder_C = %d  Encoder_D=%d\r\n",vcc,encoder_A,encoder_B);				//��ӡ��ǰ��ѹ������С�������λ
}
   
