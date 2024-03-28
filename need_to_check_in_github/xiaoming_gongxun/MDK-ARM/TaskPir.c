#include "TaskPir.h"
#include "adc.h"
uint16_t ADC_value[4];     //adc读值
int ADC_get(void)
{	
	HAL_ADC_Start(&hadc1);	//启动ADC转换
	HAL_ADC_PollForConversion(&hadc1, 50);	//等待转换完成，50ms为最大等待时间
	if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC))
	{
		for(int i = 0; i < 4; i++)
		{
			ADC_value[i] = HAL_ADC_GetValue(&hadc1);		//获取AD值
		}
	}
	return 0;
}
