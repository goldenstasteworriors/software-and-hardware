#include "moto.h"

float Velcity_Kp=0.2,  Velcity_Ki=0.1,  Velcity_Kd; //����ٶ�PID����
/**************************************************************************
�������ܣ����������ת
��ڲ�����mode   mode=0ʱΪ��ת  mode=1ʱ��ת
����  ֵ����
**************************************************************************/


void moto(int mode)
{
	if(mode==1)    //˳ʱ��ת��
	{
	 GPIO_SetBits(GPIOC, GPIO_Pin_14);	 // �ߵ�ƽ      PC14 --- AIN2      1   
	 GPIO_ResetBits(GPIOC, GPIO_Pin_13);	 // �͵�ƽ}   PC13 --- AIN1      0
	
	 GPIO_SetBits(GPIOB, GPIO_Pin_13);     //�ߵ�ƽ   PB13 --- BIN2       1
	 GPIO_ResetBits(GPIOB, GPIO_Pin_12);  // �͵�ƽ   PB12 --- BIN1       0
		
	 GPIO_SetBits(GPIOB, GPIO_Pin_1);     //�ߵ�ƽ   PB1 --- CIN2       1
	 GPIO_ResetBits(GPIOB, GPIO_Pin_0);  // �͵�ƽ   PB0 --- CIN1       0
		
	 GPIO_SetBits(GPIOC, GPIO_Pin_1);     //�ߵ�ƽ   PC2 --- DIN2       1
	 GPIO_ResetBits(GPIOC, GPIO_Pin_2);  // �͵�ƽ   PC1 --- DIN1       0
	
	}
	 if(mode==0)   //��ʱ��ת��
	{
	 GPIO_SetBits(GPIOC, GPIO_Pin_13);	 // �ߵ�ƽ       PC13 --- AIN1     1
	 GPIO_ResetBits(GPIOC, GPIO_Pin_14);	 // �͵�ƽ}    PC14 --- AIN2     0
	
	 GPIO_SetBits(GPIOB, GPIO_Pin_12);     //�ߵ�ƽ   PB12 --- BIN1     1
	 GPIO_ResetBits(GPIOB, GPIO_Pin_13);  // �͵�ƽ   PB13 --- BIN2        0
		
     GPIO_SetBits(GPIOB, GPIO_Pin_0);     //�ߵ�ƽ   PB0 --- CIN1       1
	 GPIO_ResetBits(GPIOB, GPIO_Pin_1);  // �͵�ƽ   PB1 --- CIN2       0
		
	 GPIO_SetBits(GPIOC, GPIO_Pin_2);     //�ߵ�ƽ   PC1 --- DIN1       1
	 GPIO_ResetBits(GPIOC, GPIO_Pin_1);  // �͵�ƽ   PC2 --- DIN2       0
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
	    if(ControlVelocity>7200) ControlVelocity=7200;
	    else if(ControlVelocity<-7200) ControlVelocity=-7200;
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
int Velocity_C(int TargetVelocity, int CurrentVelocity)
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
int Velocity_D(int TargetVelocity, int CurrentVelocity)
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

