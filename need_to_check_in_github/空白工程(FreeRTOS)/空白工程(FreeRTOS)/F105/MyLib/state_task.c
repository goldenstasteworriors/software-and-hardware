/************************************************************************************
ģʽ�ж�
�ж��߼�����Ҫ��Ϊ�����֣���һ�����ǿ���ģʽ����Ϊң��ģʽ������ģʽ������ģʽ��
�Զ��ǵ�ģʽ�Լ��Զ�ȡ��ģʽ
�ڶ�����Ϊ����Ŀ�꣬���ң��ģʽʱң�صĲ��֣���������ƶ��������������ϲ�������
�ϲ���������Ԯ��е�ֵȵȣ�ң����״̬���ޣ���ʱ�޸�

s1(��)������{s2�������£��ϵ�ģʽ
             s2�������ϣ���Ԯģʽ}
s1���ң�������{s2�������£�����ģʽ
               s2�������У��ֶ��ϵ�ģʽ
               s2�������ϣ��Զ��ϵ�ģʽ}						 
s1���ң�������{s2�������£�����ģʽ
               s2�������У��ֶ�ȡ��ģʽ
               s2�������ϣ��Զ�ȡ��ģʽ}
***************************************************************************************/

#include "main.h"
#include "remote.h"
#include "pid.h"
#include "can2.h"
#include "state.h"





key_control  key;
/**
  * @brief  ��·���߼��
  * @param  None
  * @retval ���ض���id
  */

u8 offline_detect(void)
{
	g_flag.offline_flag  = 0;
/**************CAN1���߼��*******************/
	if (g_flag.can1_connect == 0)
		g_flag.can1_cnt ++;
	
	if (g_flag.can1_cnt > 100)
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_13 );
		g_flag.offline_flag |= 0x01;
	}
/**************CAN2���߼��*******************/    
    if (g_flag.can2_connect == 0)
        g_flag.can2_cnt ++;
    
    if (g_flag.can2_cnt > 100)
		{
			  GPIO_ResetBits(GPIOC,GPIO_Pin_13 );
			  g_flag.offline_flag |= 0x02;
		}
		else 
	     GPIO_SetBits(GPIOC,GPIO_Pin_13 );
/**************ң�������߼��*******************/
//    if (g_flag.rc_connect == 0)
//        g_flag.rc_cnt ++;
//    
//    if (g_flag.rc_cnt > 200)
//	{
//        UART5_Configuration();        //����ң��������
//		return 3;
//	}

/**************�����Ƕ��߼��*******************/
	if (g_flag.gyro_connect == 0)
		g_flag.gyro_cnt ++;
	
	if (g_flag.gyro_cnt > 50)
	{
		g_flag.gyro_use_flag = 0;    //����
		g_flag.offline_flag |= 0x04;
	}
//	else
//		g_flag.gyro_use_flag = 1;    //��������
/**************��������*******************/
	return g_flag.offline_flag;
}


/**
  * @brief  ģʽ�ж�
  * @param  None
* @retval s1: 1:����ģʽ
			  2:�ϵ�ģʽ
			  3:ң��ģʽ
  */
void switch_mode(void)
{
	if (rc_ctrl.rc.s1 == 2)            
	{
		      
		      if(rc_ctrl.rc.s2 == 1)//����ģʽ
					{
						  g_flag.control_mode = KEY_MODE;
								
					}
					  else if(rc_ctrl.rc.s2 == 3)//��Ԯģʽ
					{
						g_flag.control_mode = SAVE_MODE;
					}
					 else if (rc_ctrl.rc.s2 == 2)   //�ϵ�ģʽ
						 {
							 g_flag.control_mode = POWER_OFF_MODE;
							 key_control_Init();

						 }
	}
	else if (rc_ctrl.rc.s1 == 3)      
	{
		        
           if(rc_ctrl.rc.s2 == 3) //�ֶ��ϵ�ģʽ
						 {	
						 g_flag.control_mode = MANUAL_LAND_MODE;

						 }
					else  if (rc_ctrl.rc.s2 == 2)//ң��ģʽ
					 {
						 g_flag.control_mode = RC_MODE;
		         g_flag.landing_state = STATE0;
						 key.flag_lift_up_mode = 0;
						 key.flag_key_mode = 0;
						 key_control_Init();
					 }
			      else if (rc_ctrl.rc.s2 == 1) //�����Զ��ϵ�
		        {
				      g_flag.control_mode = LANDING_ON_MODE;

			      }
	}
	else if (rc_ctrl.rc.s1 == 1)      
	{
		           
		           if (rc_ctrl.rc.s2 == 1)   //�����Զ�ȡ��
		           {
								 g_flag.control_mode = GET_BULLET_MODE;
								 g_flag.landing_state = STATE0;

		            }
		           else if(rc_ctrl.rc.s2 == 3)//�ֶ�ȡ��ģʽ
						  {
							  g_flag.control_mode = MANUAL_GET_BULLET_MODE;

						  }
		
		           else if (rc_ctrl.rc.s2 == 2)   //����    
		           {
			           g_flag.control_mode = LIFT_UP_MODE;
		           }
	}
	
	
	        
						  if(rc_ctrl.key.b == 1 && rc_ctrl.key.ctrl == 1) //�ֶ��ϵ�ģʽ
							  {	
								  key_control_Init();
								  key.flag_manual_landing_mode = 1;
							  }
							else if (rc_ctrl_last.key.b == 0 && rc_ctrl.key.b == 1) //�����Զ��ϵ�
							  {
								  key_control_Init();
									key.flag_landing_mode = 1;
								
						   	}
								else if(rc_ctrl.key.r == 1 && rc_ctrl.key.ctrl == 1)//�ֶ�ȡ��ģʽ
								 {
								  	key_control_Init();
                    key.flag_manual_get_buttel_mode = 1;
								 }
			
							else if (rc_ctrl_last.key.r == 0 && rc_ctrl.key.r == 1 )   //�����Զ�ȡ��
								 {
								  	key_control_Init();
									 	key.flag_get_buttel_mode = 1;

									}
							else if (rc_ctrl.key.c == 1&&rc_ctrl.key.ctrl == 1)   //�½�   
								 {
										key_control_Init();

									  
								 }
							else if (rc_ctrl_last.key.c == 0 && rc_ctrl.key.c == 1)   //����    
								 {
										key_control_Init();
									 	key.flag_lift_up_mode = 1;
									  
								 }
							else if (rc_ctrl_last.key.v == 0 && rc_ctrl.key.v == 1)//��Ԯ
								 {
									 key_control_Init();
								   key.flag_save_mode = 1;
								 } 
							else if (rc_ctrl.key.e == 1&&rc_ctrl.key.shift == 1)//��ʼ��
							{
								key_control_Init();
								key.flag_initialize_mode = 1;
							}
							else if (rc_ctrl_last.key.e == 0 && rc_ctrl.key.e == 1)//����
							   {
									 key_control_Init();
								   key.flag_key_mode = 1;
								 }
								  

								 

				if(key.flag_landing_mode == 1)
				{
					 g_flag.control_mode = LANDING_ON_MODE;

				}
				else if(key.flag_manual_landing_mode == 1)
				{

					 g_flag.control_mode = MANUAL_LAND_MODE;

				}
				else if(key.flag_get_buttel_mode == 1)
				{

					g_flag.control_mode = GET_BULLET_MODE;

				}
				else if(key.flag_get_buttel_mode1 == 1)
				{

					g_flag.control_mode = GET_BULLET_MODE1;	
					
				}
				else if(key.flag_manual_get_buttel_mode == 1)
				{
					g_flag.control_mode = MANUAL_GET_BULLET_MODE;

				}
				else if(key.flag_key_mode == 1)
				{

					g_flag.control_mode = KEY_MODE;
					
				}
				else if(key.flag_lift_up_mode == 1)
				{
					g_flag.control_mode = LIFT_UP_MODE;
					
				}
				else if(key.flag_save_mode == 1)
				{

					g_flag.control_mode = SAVE_MODE;
				}
				else if(key.flag_initialize_mode == 1)
				{
					g_flag.control_mode = INITIALIZE_MODE;
				}
				else if(key.flag_choose_mode== 1)
				{
					g_flag.control_mode = CHOOSE_MODE;
					
				}
				
}

void  key_control_Init(void)
{
	key.flag_save_mode = 0;
	key.flag_landing_mode = 0;
	key.flag_manual_landing_mode = 0;
	key.flag_get_buttel_mode = 0;
	key.flag_manual_get_buttel_mode = 0;
	key.flag_key_mode = 0;
	key.flag_lift_up_mode = 0;
  key.flag_initialize_mode = 0;
	key.flag_get_buttel_mode1 = 0;
	key.flag_choose_mode = 0;
}
