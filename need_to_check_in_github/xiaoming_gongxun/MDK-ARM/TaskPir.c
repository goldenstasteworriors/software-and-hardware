#include "TaskPir.h"
#include "adc.h"
uint16_t ADC_value[4];     //adc��ֵ
int ADC_get(void)
{	
	HAL_ADC_Start(&hadc1);	//����ADCת��
	HAL_ADC_PollForConversion(&hadc1, 50);	//�ȴ�ת����ɣ�50msΪ���ȴ�ʱ��
	if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC))
	{
		for(int i = 0; i < 4; i++)
		{
			ADC_value[i] = HAL_ADC_GetValue(&hadc1);		//��ȡADֵ
		}
	}
	return 0;
}
