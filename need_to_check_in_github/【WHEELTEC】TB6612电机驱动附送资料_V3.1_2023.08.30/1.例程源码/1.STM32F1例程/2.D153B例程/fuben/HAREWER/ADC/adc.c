#include "adc.h"
#include "delay.h"
#include "usart.h"

/**************************************************************************
�������ܣ�ADC1��ʼ������
��ڲ�������
����  ֵ����
**************************************************************************/

void adc1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;            //����ṹ��GPIO_InitStructure
	ADC_InitTypeDef ADC_InitStructure;          //����ṹADC_InitStructure

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1, ENABLE);	//����GPIOA��ADC1ʱ��

	//PA4 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	ADC_DeInit(ADC1);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//��ʹ��ɨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ����ʹ������ת��
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת���������������ʹ���ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ1
	
	ADC_Init(ADC1, &ADC_InitStructure);	//ADC��ʼ��ʹ��adc1
	
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  
	
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����

	
	ADC_StartCalibration(ADC1);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����

}


/**************************************************************************
�������ܣ�ACD2��ʼ������
��ڲ�������
����  ֵ����
**************************************************************************/

void adc2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;            //����ṹ��GPIO_InitStructure
	ADC_InitTypeDef ADC_InitStructure;          //����ṹADC_InitStructure

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC2, ENABLE);	//����GPIOA��ADC2ʱ��

	//PA5 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	ADC_DeInit(ADC2);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//��ʹ��ɨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ����ʹ������ת��
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת���������������ʹ���ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ1
	
	ADC_Init(ADC2, &ADC_InitStructure);	//ADC��ʼ��ʹ��adc1
	
	ADC_Cmd(ADC2, ENABLE);	//ʹ��ָ����ADC2
	
	ADC_ResetCalibration(ADC2);	//ʹ�ܸ�λУ׼  
	
	while(ADC_GetResetCalibrationStatus(ADC2));	//�ȴ���λУ׼����

	
	ADC_StartCalibration(ADC2);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC2));	 //�ȴ�У׼����

}


/**************************************************************************
�������ܣ����ADC1ֵ
��ڲ�����ch ͨ��ֵ 0~3
����  ֵ���������һ��ADC1�������ת�����
**************************************************************************/

u16  Get_adc1(u8 ch)
{   
			//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}



/**************************************************************************
�������ܣ����ADC2ֵ
��ڲ�����ch ͨ��ֵ 0~3
����  ֵ���������һ��ADC2�������ת�����
**************************************************************************/

u16  Get_adc2(u8 ch)
{   
			//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC2, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
  
	ADC_SoftwareStartConvCmd(ADC2, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC2);	//�������һ��ADC1�������ת�����
}


/**************************************************************************
�������ܣ���ȡadc����������
��ڲ�����ch ͨ��ֵ 0~3
����  ֵ��times
**************************************************************************/

u16 Get_adc1_Average(u8 ch,u8 times)
{ 		    		  			    
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_adc1(ch);
		delay_ms(5);
	}
	return temp_val/times;
	
}



/**************************************************************************
�������ܣ���ȡadc2����������
��ڲ�����ch ͨ��ֵ 0~3
����  ֵ��times
**************************************************************************/

u16 Get_adc2_Average(u8 ch,u8 times)
{ 		    		  			    
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_adc2(ch);
		delay_ms(5);
	}
	return temp_val/times;


}

