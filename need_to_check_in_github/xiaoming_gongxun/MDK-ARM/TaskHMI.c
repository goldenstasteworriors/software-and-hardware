#include "TaskHMI.h"
#include "stdio.h"
extern UART_HandleTypeDef huart6;

void HMISends(uint8_t *buf1)		 
{
	uint8_t i=0;
	while(1)
	{
	 if(buf1[i]!=0)
	 	{		
			HAL_UART_Transmit(&huart6,&buf1[i],sizeof(buf1[i]),100000);
			while(HAL_UART_GetState(&huart6)==RESET){};
		 	i++;
		}
	 else 
	 return ;

	}
}

void HMISendb(uint8_t k)
{		 
	uint8_t i;
	 for(i=0;i<3;i++)
	 {
	 if(k!=0)
	 	{
			  
			HAL_UART_Transmit(&huart6,&k,sizeof(k),10000);
			while(HAL_UART_GetState(&huart6)==RESET){};
		}
	 else 
		return ;
	 } 
} 

//Start
void HMISendstart(void)
{
	 	//HAL_Delay(200);

		HMISendb(0xff);
		//HAL_Delay(200);
}

//TEXT
void textHMI(char *buf, float var)
{
	//sprintf((char *)buf,"page0.t1.txt=\"%d\"",var); 
	//HMISends((char *)buf);
	//HMISendb(0xff);

	sprintf((char *)buf,"page0.t0.txt=\"Wait...\"");
	HMISends((uint8_t *)buf);
	HMISendb(0xff);

}
//num
void numHMI(char *buf, uint8_t var)
{
	sprintf((char *)buf,"n0.val=%d",var);
	HMISends((uint8_t *)buf);
	HMISendb(0xff);

}
//float
void floatHMI(char *buf, uint8_t num, uint8_t vvs)
{
	sprintf((char *)buf,"x0.val=%d",num);
	HMISends((uint8_t *)buf);
	HMISendb(0xff);
	sprintf((char *)buf,"x0.vvs1=%d",vvs);	
	HMISends((uint8_t *)buf);
	HMISendb(0xff);
}
//	QuXian(not used)
void lineHMI(char *buf, uint8_t ExchangeSpeed1)
{
	sprintf((char *)buf,"add 1,1,%d",ExchangeSpeed1);
	HMISends((uint8_t *)buf);
  HMISendb(0xff);

}



/*
HAL_UART_Receive_IT(&huart2,&Res,1);
switch(Res)
{
case 0x31 : {sprintf((char *)buf,"page1.t0.txt=\"?\"");
							HMISends((char *)buf);
							HMISendb(0xff);
							break;}
case 0x32 : {sprintf((char *)buf,"page2.t0.txt=\"?\"");
						 HMISends((char *)buf);
						HMISendb(0xff);
						break;}
case 0x33 : {sprintf((char *)buf,"page3.t0.txt=\"?\"");
						HMISends((char *)buf);
						HMISendb(0xff);
						break;}
}
*/
