/************************************************************************************
CAN2控制机械手的移动以及陀螺仪数据接收，ID号如下：

陀螺仪数据接收：0x301、0x302
***************************************************************************************/

#include "main.h"
#include "can2.h"
#include "pid.h"
#include "string.h"

rmc610_t move_motor;       //机械手移动电机


float yaw_angle;
float gz;

extern pid_Typedef chassis_pos_follow_pid;
extern pid_Typedef getbullet_vel_pid;
/**
  * @brief  配置CAN2
  * @param  None
  * @retval None
  */
void CAN2_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	CAN_InitTypeDef        CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;

	/* 打开GPIO时钟、AFIO时钟，CAN时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);

	/* CAN2 RX PB12 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	/* CAN2 TX PB13 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);								

	/* CAN2 Enabling interrupt */								 	  
	NVIC_Config(CAN2_RX0_IRQn, 2, 0);
	NVIC_Config(CAN2_RX1_IRQn, 2, 1);
	NVIC_Config(CAN2_TX_IRQn, 2, 2);
	
	/* CAN  BaudRate = RCC_APB1PeriphClock/(CAN_SJW+CAN_BS1+CAN_BS2)/CAN_Prescaler */
	CAN_DeInit(CAN2);
	CAN_StructInit(&CAN_InitStructure);   

	CAN_InitStructure.CAN_TTCM=DISABLE;
	CAN_InitStructure.CAN_ABOM=DISABLE;
	CAN_InitStructure.CAN_AWUM=DISABLE;
	CAN_InitStructure.CAN_NART=ENABLE;
	CAN_InitStructure.CAN_RFLM=DISABLE;
	CAN_InitStructure.CAN_TXFP=DISABLE;
	CAN_InitStructure.CAN_Mode=CAN_Mode_Normal;   
	//CAN_InitStructure.CAN_Mode=CAN_Mode_LoopBack;
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1=CAN_BS1_5tq;  
	CAN_InitStructure.CAN_BS2=CAN_BS2_3tq;	
	CAN_InitStructure.CAN_Prescaler=4;

	CAN_Init(CAN2,&CAN_InitStructure);   // CAN2													

	CAN_FilterInitStructure.CAN_FilterNumber=14;	// 
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdList;	 // 标识符屏蔽位模式
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_16bit;   // 32位过滤器
	CAN_FilterInitStructure.CAN_FilterIdHigh=0x201 << 5;			// 过滤器标识符
	CAN_FilterInitStructure.CAN_FilterIdLow=0x202 << 5;				
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x205 << 5;		
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x206 << 5;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;	 // FIFO0指向过滤器
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);

	CAN_FilterInitStructure.CAN_FilterNumber=15;	// 
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdList;	 // 标识符屏蔽位模式
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;   // 32位过滤器
	CAN_FilterInitStructure.CAN_FilterIdHigh=0x100 << 5;			// 过滤器标识符
	CAN_FilterInitStructure.CAN_FilterIdLow=0 | CAN_ID_STD;				
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh= 0x101 << 5;		
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0 | CAN_ID_STD;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO1;	 // FIFO0指向过滤器
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	CAN_ITConfig(CAN2,CAN_IT_FMP0,ENABLE);  // CAN2
	CAN_ITConfig(CAN2,CAN_IT_FMP1,ENABLE); 
	CAN_ITConfig(CAN2,CAN_IT_TME,ENABLE);
}

/**
  * @brief  CAN2接收中断，FIFO0
  * @param  None
  * @retval None
  */
void CAN2_RX0_IRQHandler(void)
{
	CanRxMsg rx_message;
	if(CAN_GetITStatus(CAN2,CAN_IT_FMP0) != RESET) 
	{
        CAN_Receive(CAN2, CAN_FIFO0, &rx_message);	
		switch(rx_message.StdId)
        {
            case 0x205:
                move_motor.angle = (rx_message.Data[0] << 8) | rx_message.Data[1];
                move_motor.speed = (rx_message.Data[2] << 8) | rx_message.Data[3];
				if ((move_motor.angle - move_motor.last_angle) > 5000)
				{
					move_motor.cycle++;
				}
				if ((move_motor.angle - move_motor.last_angle) < -5000)
				{
					move_motor.cycle--;
				}
				move_motor.real_posion = (-move_motor.cycle * 8192.0f + move_motor.angle) / 19.0f;
				move_motor.last_angle = move_motor.angle;
            break;
			
			default:
			break;
		}
		
		g_flag.can2_cnt = 0;
		g_flag.can2_connect = 0;
        
		CAN_ClearITPendingBit(CAN2, CAN_IT_FMP0);
	}
}	
	
/**
  * @brief  CAN2接收中断，FIFO1
  * @param  None
  * @retval None
  */
CanRxMsg rx_message_1;	
void CAN2_RX1_IRQHandler(void)
{
	if(CAN_GetITStatus(CAN2, CAN_IT_FMP1) != RESET) 
	{
        CAN_Receive(CAN2, CAN_FIFO1, &rx_message_1);	
		if (rx_message_1.StdId == 0x101)
		{
			memcpy(&yaw_angle,&rx_message_1.Data,4);
			memcpy(&gz,&(rx_message_1.Data[4]),4);
			
		}
		
		g_flag.gyro_cnt = 0;
		g_flag.gyro_connect = 0;
		if(g_flag.gyro_initial_flag == 0)
		{
			g_flag.gyro_initial_flag = 1;
			chassis_pos_follow_pid.SetPoint = yaw_angle;
		}
				
		CAN_ClearITPendingBit(CAN2, CAN_IT_FMP1);
	}
}

/**
  * @brief  CAN2发送中断
  * @param  None
  * @retval None
  */
void CAN2_TX_IRQHandler(void)
{
	if(CAN_GetITStatus(CAN2, CAN_IT_TME) != RESET) 
	{
		CAN_ClearITPendingBit(CAN2, CAN_IT_TME);
	}
}

/**
  * @brief  CAN2发送数据 0x200，升降
  * @param  a：0x201电流给定
            b：0x202电流给定
            c：0x203电流给定
            d：0x204电流给定
  * @retval None
  */
void can2_move_send(int a)
{
    CanTxMsg tx_message;
    tx_message.IDE = CAN_ID_STD;    
    tx_message.RTR = CAN_RTR_DATA; 
    tx_message.DLC = 0x08;    
    tx_message.StdId = 0x1FF;
	
    a = LIMIT_MAX_MIN(a, 5000, -5000);        //对升降电机进行限流，防止机构损坏

    tx_message.Data[0] = (unsigned char)((a >> 8) & 0xff);
    tx_message.Data[1] = (unsigned char)(a & 0xff);  
    tx_message.Data[2] = 0;
    tx_message.Data[3] = 0;
    tx_message.Data[4] = 0;
    tx_message.Data[5] = 0;
    tx_message.Data[6] = 0; 
    tx_message.Data[7] = 0;

    CAN_Transmit(CAN2, &tx_message);
}

/**
  * @brief  CAN2发送数据 0x1FFF，侧向移动
  * @param  a：0x201电流给定
            b：0x202电流给定
            c：0x203电流给定
            d：0x204电流给定
  * @retval None
  */
void can2_lateral_send(int a)
{
    CanTxMsg tx_message;
    tx_message.IDE = CAN_ID_STD;    
    tx_message.RTR = CAN_RTR_DATA; 
    tx_message.DLC = 0x08;    
    tx_message.StdId = 0x1FF;
	
    a = LIMIT_MAX_MIN(a, 6000, -6000);
	  
	
    tx_message.Data[0] = (unsigned char)((a >> 8) & 0xff);
    tx_message.Data[1] = (unsigned char)(a & 0xff);  
    tx_message.Data[2] = 0;
    tx_message.Data[3] = 0;
    tx_message.Data[4] = 0;
    tx_message.Data[5] = 0;
    tx_message.Data[6] = 0; 
    tx_message.Data[7] = 0;

    CAN_Transmit(CAN2, &tx_message);
}

/**
  * @brief  获取YAW轴角度
  * @param  None
  * @retval None
  */
float get_yaw_angle(void)
{
	return yaw_angle;
}

/**
  * @brief  获取YAW轴角速度
  * @param  None
  * @retval None
  */
float get_gz(void)
{
	return gz;
}
