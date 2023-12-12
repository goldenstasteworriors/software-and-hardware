/************************************************************************************
CAN1���Ƶ������Ĵ���ID�����£�
			ͷ
			|
	0x201	|   0x204
			|
��������������������������������������������������������
			|
	0x202	|   0x203
			|
		β��צ�ӣ�
		
	0x205		0x206
***************************************************************************************/

#include "main.h"
#include "can1.h"

/*NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4)*/

rmc620_t track_motor[2];
rmc620_t chassis_motor[4];

/**
  * @brief  ����CAN1
  * @param  None
  * @retval None
  */
void CAN1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	CAN_InitTypeDef        CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;

	/* ��GPIOʱ�ӡ�AFIOʱ�ӣ�CANʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);


	/* CAN1 RX PB8 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	/* CAN1 TX PB9 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_PinRemapConfig(GPIO_Remap1_CAN1,ENABLE);  // CAN1 remap

	/* CAN1 Enabling interrupt */	
	NVIC_Config(CAN1_RX0_IRQn, 0, 0);									
	NVIC_Config(CAN1_TX_IRQn, 1, 0);
	
	/* CAN  BaudRate = RCC_APB1PeriphClock/(CAN_SJW+CAN_BS1+CAN_BS2)/CAN_Prescaler */
	CAN_DeInit(CAN1);
	CAN_StructInit(&CAN_InitStructure);   

	CAN_InitStructure.CAN_TTCM=DISABLE;
	CAN_InitStructure.CAN_ABOM=ENABLE;
	CAN_InitStructure.CAN_AWUM=ENABLE;
	CAN_InitStructure.CAN_NART=ENABLE;
	CAN_InitStructure.CAN_RFLM=DISABLE;
	CAN_InitStructure.CAN_TXFP=ENABLE;
	CAN_InitStructure.CAN_Mode=CAN_Mode_Normal;   
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1=CAN_BS1_5tq;  
	CAN_InitStructure.CAN_BS2=CAN_BS2_3tq;	
	CAN_InitStructure.CAN_Prescaler=4;

	CAN_Init(CAN1,&CAN_InitStructure);	// CAN1											

	CAN_FilterInitStructure.CAN_FilterNumber=0;	 
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;	 // ��ʶ������λģʽ
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;   // 32λ������
	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;			// ��������ʶ��
	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;				
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;		// ���������α�ʶ��
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;	 // FIFO0ָ�������
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
//	CAN1->IER = 0x03;

    CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
    CAN_ITConfig(CAN1,CAN_IT_TME,ENABLE);
}

/**
  * @brief  CAN1�����ж�
  * @param  None
  * @retval None
  */
void CAN1_RX0_IRQHandler(void)
{
	CanRxMsg rx_message;
	if(CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET) 
	{
		CAN_Receive(CAN1, CAN_FIFO0, &rx_message);
		
		switch(rx_message.StdId)
        {
            case 0x201:                                                          
                chassis_motor[0].angle = (rx_message.Data[0] << 8) | rx_message.Data[1];
                chassis_motor[0].speed = (rx_message.Data[2] << 8) | rx_message.Data[3];
            break;
            
            case 0x202:
                chassis_motor[1].angle = (rx_message.Data[0] << 8) | rx_message.Data[1];
                chassis_motor[1].speed = (rx_message.Data[2] << 8) | rx_message.Data[3];
            break;
            
            case 0x203:
                chassis_motor[2].angle = (rx_message.Data[0] << 8) | rx_message.Data[1];
                chassis_motor[2].speed = (rx_message.Data[2] << 8) | rx_message.Data[3];
            break;
            
            case 0x204:
                chassis_motor[3].angle = (rx_message.Data[0] << 8) | rx_message.Data[1];
                chassis_motor[3].speed = (rx_message.Data[2] << 8) | rx_message.Data[3];
            break;    
			
			case 0x205:
				track_motor[0].angle = (rx_message.Data[0] << 8) | rx_message.Data[1];
                track_motor[0].speed = (rx_message.Data[2] << 8) | rx_message.Data[3];
				if((track_motor[0].angle - track_motor[0].last_angle) > 5000)
				{
					track_motor[0].cycle++;
				}
				if((track_motor[0].angle - track_motor[0].last_angle) < -5000)
				{
					track_motor[0].cycle--;
				}
				track_motor[0].last_angle = track_motor[0].angle;
			break;
				
			case 0x206:
				track_motor[1].angle = (rx_message.Data[0] << 8) | rx_message.Data[1];
                track_motor[1].speed = (rx_message.Data[2] << 8) | rx_message.Data[3];
				if((track_motor[1].angle - track_motor[1].last_angle) > 5000)
				{
					track_motor[1].cycle++;
				}
				if((track_motor[1].angle - track_motor[1].last_angle) < -5000)
				{
					track_motor[1].cycle--;
				}
				track_motor[1].last_angle = track_motor[1].angle;
			break;
				
			default:
				break;
		}
		
		g_flag.can1_cnt= 0;
    g_flag.can1_connect = 0;
		
		CAN_ClearITPendingBit(CAN1,CAN_IT_FMP0);
	}
}	

/**
  * @brief  CAN1�����ж�
  * @param  None
  * @retval None
  */
void CAN1_TX_IRQHandler(void)
{
	if(CAN_GetITStatus(CAN1,CAN_IT_TME)!= RESET) 
	{
		CAN_ClearITPendingBit(CAN1,CAN_IT_TME);
	}
}


/**
  * @brief  CAN1��������,�ڴ������޷� -16384 ~ 0 ~ 16384
  * @param  a��0x201��������
            b��0x202��������
            c��0x203��������
            d��0x204��������
  * @retval None
  */
void chassis_current_send(int a, int b, int c, int d)
{
    CanTxMsg tx_message;
    tx_message.IDE = CAN_ID_STD;    
    tx_message.RTR = CAN_RTR_DATA; 
    tx_message.DLC = 0x08;    
    tx_message.StdId = 0x200;
	
    a = LIMIT_MAX_MIN(a, 15000, -15000);
    b = LIMIT_MAX_MIN(b, 15000, -15000);
    c = LIMIT_MAX_MIN(c, 15000, -15000);
    d = LIMIT_MAX_MIN(d, 15000, -15000);
	
    tx_message.Data[0] = (unsigned char)((a >> 8) & 0xff);
    tx_message.Data[1] = (unsigned char)(a & 0xff);  
    tx_message.Data[2] = (unsigned char)((b >> 8) & 0xff);
    tx_message.Data[3] = (unsigned char)(b & 0xff);
    tx_message.Data[4] = (unsigned char)((c >> 8) & 0xff);
    tx_message.Data[5] = (unsigned char)(c & 0xff);
    tx_message.Data[6] = (unsigned char)((d >> 8) & 0xff); 
    tx_message.Data[7] = (unsigned char)(d & 0xff);

    CAN_Transmit(CAN1, &tx_message);
}

/**
  * @brief  CAN1��������,�ڴ������޷� -16384 ~ 0 ~ 16384
  * @param  left��0x205��������
			right��0x206��������
  * @retval None
  */
void track_current_send(int left, int right)
{
	CanTxMsg tx_message;
	int i;
    tx_message.IDE = CAN_ID_STD;    
    tx_message.RTR = CAN_RTR_DATA; 
    tx_message.DLC = 0x08;    
    tx_message.StdId = 0x1FF;
	
    left = LIMIT_MAX_MIN(left, 15000, -15000);
    right = LIMIT_MAX_MIN(right, 15000, -15000);
	  
    tx_message.Data[0] = (unsigned char)((left >> 8) & 0xff);
    tx_message.Data[1] = (unsigned char)(left & 0xff);  
    tx_message.Data[2] = (unsigned char)((right >> 8) & 0xff);
    tx_message.Data[3] = (unsigned char)(right & 0xff);
	for(i=0;i<4;i++)
		tx_message.Data[4+i] = 0;
		
    CAN_Transmit(CAN1, &tx_message);
}
