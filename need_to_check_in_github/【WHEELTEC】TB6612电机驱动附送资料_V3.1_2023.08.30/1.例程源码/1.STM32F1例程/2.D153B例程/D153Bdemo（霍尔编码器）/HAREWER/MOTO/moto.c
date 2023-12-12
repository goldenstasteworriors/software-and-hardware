#include "moto.h"


/**************************************************************************
�������ܣ����������ת
��ڲ�����mode   mode=0ʱΪ��ת  mode=1ʱ��ת
����  ֵ����
**************************************************************************/

extern float Velcity_Kp,  Velcity_Ki,  Velcity_Kd; //����ٶ�PID����


void moto(int mode)
{
	if(mode==1)    //��ת
	{
	 GPIO_SetBits(GPIOB, GPIO_Pin_15);	 // �ߵ�ƽ      PB15 --- AIN2      1   
	 GPIO_ResetBits(GPIOB, GPIO_Pin_14);	 // �͵�ƽ}   PB14 --- AIN1      0
	
	 GPIO_SetBits(GPIOB, GPIO_Pin_13);     //�ߵ�ƽ   PB13 --- BIN2       1
	 GPIO_ResetBits(GPIOB, GPIO_Pin_12);  // �͵�ƽ   PB12 --- BIN1       0
	
	}
	 if(mode==0)   //����
	{
	 GPIO_SetBits(GPIOB, GPIO_Pin_14);	 // �ߵ�ƽ       PB14 --- AIN1     1
	 GPIO_ResetBits(GPIOB, GPIO_Pin_15);	 // �͵�ƽ}    PB15 --- AIN2     0
	
	 GPIO_ResetBits(GPIOB, GPIO_Pin_13);     //�ߵ�ƽ   PB13 --- BIN2     0
	 GPIO_SetBits(GPIOB, GPIO_Pin_12);  // �͵�ƽ   PB12 --- BIN1         1
	 }
 
}
/***************************************************************************
�������ܣ�����ıջ�����
��ڲ��������ҵ���ı�����ֵ
����ֵ  �������PWM
***************************************************************************/

int Velocity_A(int TargetVelocity, int CurrentVelocity)
{
		int Bias;  //������ر���
		static int ControlVelocity, Last_bias; //��̬�������������ý�������ֵ��Ȼ����
		
		Bias=TargetVelocity-CurrentVelocity; //���ٶ�ƫ��
		
		ControlVelocity+=Velcity_Kp*(Bias-Last_bias)+Velcity_Ki*Bias;  //����ʽPI������
                                                                   //Velcity_Kp*(Bias-Last_bias) ����Ϊ���Ƽ��ٶ�
	                                                                 //Velcity_Ki*Bias             �ٶȿ���ֵ��Bias���ϻ��ֵõ� ƫ��Խ����ٶ�Խ��
		Last_bias=Bias;	
		return ControlVelocity; //�����ٶȿ���ֵ
	
}
int Velocity_B(int TargetVelocity, int CurrentVelocity)
{
		int Bias;  //������ر���
		static int ControlVelocity, Last_bias; //��̬�������������ý�������ֵ��Ȼ����
		
		Bias=TargetVelocity-CurrentVelocity; //���ٶ�ƫ��
		
		ControlVelocity+=Velcity_Kp*(Bias-Last_bias)+Velcity_Ki*Bias;  //����ʽPI������
                                                                   //Velcity_Kp*(Bias-Last_bias) ����Ϊ���Ƽ��ٶ�
	                                                                 //Velcity_Ki*Bias             �ٶȿ���ֵ��Bias���ϻ��ֵõ� ƫ��Խ����ٶ�Խ��
		Last_bias=Bias;	
		return ControlVelocity; //�����ٶȿ���ֵ
	
}


