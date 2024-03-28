#include "TaskTop.h"
#include "FreeRTOS.h"
#include "myqueue.h"
#include "TaskMearm.h"
#include "main.h"
#include "stm32f4xx_it.h"
#include "TaskMotor.h"
#define GRAB_TIME 10000
#define MEARM_TIME 1800			//��е�۶������ʱ��
const double pos_y[3] = {0.341,0.364,0.381};		//Բ����Ӧ��y
const double pos_z = -0.029;		//Բ����Ӧ��z
const double pos_z2 = 0.05;		//Բ����Ӧ��z2
const float POS_GM[3] = {276.6,252.8,297.7};	//�ӹ���Բ����Ӧ����̨�Ƕ� 276.0,248.5,300.0
const float POS_GM_S[3] = {6.6,-17.2,27.7};   //���ӹ���Բ����Ӧ����̨�Ƕ�
//��е�۲�ͬ�ط����˶�λ��   						mode  GM_angle  PointY  Point Z  clip_angle  time[4]
const MecArmAttiSturcture scan_color ={0,   270,    0.28,    0.13,    35,     {0, 0, 0, 0}};
const MecArmAttiSturcture scan_cor_0 ={0,   315,    0.23,    0.16,    -4,     {0, 0, 0, 0}};
const MecArmAttiSturcture scan_cor ={0,   315,    0.28,    0.10,    -4,     {0, 0, 0, 0}};
const MecArmAttiSturcture back={0,   315,    0.27,    0.15,    -30,     {0, 0, 0, 0}};
const MecArmAttiSturcture scan_circle_0 ={0,   270,    0.2,    0.16,    -4,     {0, 0, 0, 0}};		//ɨ��Բ������
const MecArmAttiSturcture scan_circle ={0,   270,    0.38,    0.09,    -4,     {0, 0, 0, 0}};		//ɨ��Բ������
const MecArmAttiSturcture scan_circle2_0 ={0,   0,    0.2,    0.20,    -4,     {0, 0, 0, 0}};			//ɨϸԲ������
const MecArmAttiSturcture scan_circle2 ={0,   0,    0.38,    0.09,     -4,     {0, 0, 0, 0}};			//ɨϸԲ������
const MecArmAttiSturcture scan_circle2_2 ={0,   0,    0.37,    0.20,     -4,     {0, 0, 0, 0}};		//ɨϸԲ������
const MecArmAttiSturcture atti ={1,   270,    0.07,    0.05,    -4,     {0, 0, 0, 0}};						//�ƶ�ʱ������
const MecArmAttiSturcture atti2 ={1,   270,    0.07,    0.05,    -4,     {0, 0, 0, 0}};						//�ƶ�ʱ������
extern QueueHandle_t	ArmAttitudeQueueHandle;
extern QueueHandle_t RasperryitemQueueHandle,RasperryDataQueueHandle,RasperryQRQueueHandle,RasperryfianlQueueHandle;
extern QueueHandle_t WORK1QueueHandle;
extern UART_HandleTypeDef huart2;
extern OderSturcture rx_oder;
GM_PUTANGLE s1_angle,s2_angle;
uint8_t rasp_data_rx[4];	//��Ϣ���н������ݻ�����
void Action_QR(void)
{
	uint8_t cmd = '1';
	move_to(-130,0, 0);
	Waitfinishmoving();
	move_to(0,580, 0);
	Waitfinishmoving();
	Move_Servo(26,-146,-86,0,0,0,0);//(66,-120,32,0,0,0,0);		//��е�����ƣ�ɨ��ά��
	vTaskDelay(600);
	HAL_UART_Transmit(&huart2,&cmd,sizeof(cmd),100000);		//����ݮ�ɷ����ݣ�ɨ��ά��
	vTaskDelay(100);
	
}
void Action_color(void)
{
	if(xQueueReceive(RasperryQRQueueHandle, &rasp_data_rx[0], portMAX_DELAY))
	{
	move_to(0, 920, 0);	
	Waitfinishmoving();
	Mearm_Move(scan_cor);		\
	GM_detect();
	vTaskDelay(600);
	position_correct();
	vTaskDelay(600);
	Mearm_Move(scan_cor_0);	
	vTaskDelay(600);
	}
}
void Action_rotate_grab(int mode)
{
//-------------try code-------------//	
	
//	rx_oder.target_oder1[0]='1';
//	rx_oder.target_oder1[1]='2';
//	rx_oder.target_oder1[2]='3';
//	rx_oder.target_oder2[0]='1';
//	rx_oder.target_oder2[1]='2';
//	rx_oder.target_oder2[2]='3';
//	rx_oder.real_oder[0]='3';
//	rx_oder.real_oder[1]='1';
//	rx_oder.real_oder[2]='2';	
//	Mearm_Move(scan_cor);			
//	vTaskDelay(2000);
//	position_correct();
//	vTaskDelay(1000);
//	Mearm_Move(scan_cor_0);
	
//-------------try code-------------//
		
	
	zhua_detect();	
	GM_detect();
	vTaskDelay(500);	
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	uint8_t cmd = '2';
	int temp;
	char a[3];
	s2_angle.obj_pos[0]= 270;s2_angle.obj_pos[1]= 180;s2_angle.obj_pos[2]= 0;
	
	HAL_UART_Transmit(&huart2,&cmd,sizeof(cmd),100000);		//����ݮ��ʶ����ɫ
	vTaskDelay(60);	
	for(int i=0;i<3;i++)
		{
			a[i] = rx_oder.real_oder[i];
		}
	int j=0;
		
	if(mode==1)
	{		
		if(rx_oder.target_oder1[j] == a[0])
			vTaskDelay(4000);	
	}
	else
	{
		if(rx_oder.target_oder2[j] == a[0])
			vTaskDelay(4000);	
	}
	while(j<3)
	{		

		if (mode==1)
		{
			HAL_UART_Transmit(&huart2,&cmd,sizeof(cmd),100000);		//����ݮ��ʶ����ɫ
			vTaskDelay(80);	
			a[0] = rx_oder.real_oder[0];
			if(rx_oder.target_oder1[j] == a[0])
			{
				Grab_up(1,180,s2_angle.obj_pos[j],0.262,0.028);
				vTaskDelay(80);	
				j++;
				if(j==3)
					break;
				zhua_detect();	
				GM_detect();
				vTaskDelay(500);
			}
		}
		else
		{
			HAL_UART_Transmit(&huart2,&cmd,sizeof(cmd),100000);		//����ݮ��ʶ����ɫ
			vTaskDelay(80);	
			a[0] = rx_oder.real_oder[0];
			if(rx_oder.target_oder2[j] == a[0])
			{
				Grab_up(1,180,s2_angle.obj_pos[j],0.262,0.028);
				vTaskDelay(80);	
				j++;
				if(j==3)
					break;
				zhua_detect();	
				GM_detect();
				vTaskDelay(500);
			}
		}
//		temp = a[i];
//		a[i] = a[i+1];
//		a[i+1]=a[i+2];
//		a[i+2] = temp; 
//		vTaskDelayUntil(&xLastWakeTime, 5000);
//		i=0;		
	}
	vTaskDelay(10);	
	
}
void Action_WORK1(int mode)		//����ּӹ���
{		
//-------------try code-------------//
	
//		rx_oder.target_oder1[0]='1';
//		rx_oder.target_oder1[1]='2';
//		rx_oder.target_oder1[2]='3';
//		rx_oder.target_oder2[0]='1';
//		rx_oder.target_oder2[1]='2';
//		rx_oder.target_oder2[2]='3';
	
//-------------try code-------------//
		Mearm_Move(scan_circle_0);
		GM_detect();
		vTaskDelay(600);
		line_correct(270);
		Mearm_Move(scan_circle);
		vTaskDelay(360);
		round_correct();
		vTaskDelay(300);
		Mearm_Move(scan_circle_0);
		vTaskDelay(360);

		s1_angle.obj_pos[0] = 270;
		s1_angle.obj_pos[1] = 180;
		s1_angle.obj_pos[2] = 360;
	
		if(mode==1)
		{
			if(rx_oder.target_oder1[0]=='1' && rx_oder.target_oder1[1]=='2' && rx_oder.target_oder1[2]=='3')		//�죬�̣���
			{		
				s1_angle.circle_pos[0]= POS_GM[1]; s1_angle.circle_pos[1]=POS_GM[0]; s1_angle.circle_pos[2]=POS_GM[2];
				s1_angle.y[0]=pos_y[1];s1_angle.y[1]=pos_y[0];s1_angle.y[2]=pos_y[2];
				s1_angle.z[0]=pos_z;s1_angle.z[1]=pos_z;s1_angle.z[2]=pos_z;
				circle_logic(0,s1_angle);
				vTaskDelay(60);
				circle_logic(1,s1_angle);
			}			
			else if(rx_oder.target_oder1[0]=='1' && rx_oder.target_oder1[1]=='3' && rx_oder.target_oder1[2]=='2')		//�죬������
			{
				s1_angle.circle_pos[0]= POS_GM[1]; s1_angle.circle_pos[1]=POS_GM[2]; s1_angle.circle_pos[2]=POS_GM[0];
				s1_angle.y[0]=pos_y[1];s1_angle.y[1]=pos_y[2];s1_angle.y[2]=pos_y[0];
				s1_angle.z[0]=pos_z;s1_angle.z[1]=pos_z;s1_angle.z[2]=pos_z;
				circle_logic(0,s1_angle);
				vTaskDelay(60);
				circle_logic(1,s1_angle);
			}
			else if(rx_oder.target_oder1[0]=='2' && rx_oder.target_oder1[1]=='1' && rx_oder.target_oder1[2]=='3')		//�̣��죬��
			{
				s1_angle.circle_pos[0]= POS_GM[0]; s1_angle.circle_pos[1]=POS_GM[1]; s1_angle.circle_pos[2]=POS_GM[2];
				s1_angle.y[0]=pos_y[0];s1_angle.y[1]=pos_y[1];s1_angle.y[2]=pos_y[2];
				s1_angle.z[0]=pos_z;s1_angle.z[1]=pos_z;s1_angle.z[2]=pos_z;
				circle_logic(0,s1_angle);
				vTaskDelay(60);
				circle_logic(1,s1_angle);
			}
			else if(rx_oder.target_oder1[0]=='2' && rx_oder.target_oder1[1]=='3' && rx_oder.target_oder1[2]=='1')		//�̣�������
			{
				s1_angle.circle_pos[0]= POS_GM[0]; s1_angle.circle_pos[1]=POS_GM[2]; s1_angle.circle_pos[2]=POS_GM[1];
				s1_angle.y[0]=pos_y[0];s1_angle.y[1]=pos_y[2];s1_angle.y[2]=pos_y[1];
				s1_angle.z[0]=pos_z;s1_angle.z[1]=pos_z;s1_angle.z[2]=pos_z;
				circle_logic(0,s1_angle);
				vTaskDelay(60);
				circle_logic(1,s1_angle);
			}
			else if(rx_oder.target_oder1[0]=='3' && rx_oder.target_oder1[1]=='2' && rx_oder.target_oder1[2]=='1')		//�����̣���
			{
				s1_angle.circle_pos[0]= POS_GM[2]; s1_angle.circle_pos[1]=POS_GM[0]; s1_angle.circle_pos[2]=POS_GM[1];
				s1_angle.y[0]=pos_y[2];s1_angle.y[1]=pos_y[0];s1_angle.y[2]=pos_y[1];
				s1_angle.z[0]=pos_z;s1_angle.z[1]=pos_z;s1_angle.z[2]=pos_z;
				circle_logic(0,s1_angle);
				vTaskDelay(60);
				circle_logic(1,s1_angle);
			}
			else if(rx_oder.target_oder1[0]=='3' && rx_oder.target_oder1[1]=='1' && rx_oder.target_oder1[2]=='2')		//�����죬��
			{
				s1_angle.circle_pos[0]= POS_GM[2]; s1_angle.circle_pos[1]=POS_GM[1]; s1_angle.circle_pos[2]=POS_GM[0];
				s1_angle.y[0]=pos_y[2];s1_angle.y[1]=pos_y[1];s1_angle.y[2]=pos_y[0];
				s1_angle.z[0]=pos_z;s1_angle.z[1]=pos_z;s1_angle.z[2]=pos_z;
				circle_logic(0,s1_angle);
				vTaskDelay(60);
				circle_logic(1,s1_angle);
			}
		}
		
		else
		{
				if(rx_oder.target_oder2[0]=='1' && rx_oder.target_oder2[1]=='2' && rx_oder.target_oder2[2]=='3')		//�죬�̣���
			{		
				s1_angle.circle_pos[0]= POS_GM[1]; s1_angle.circle_pos[1]=POS_GM[0]; s1_angle.circle_pos[2]=POS_GM[2];
				s1_angle.y[0]=pos_y[1];s1_angle.y[1]=pos_y[0];s1_angle.y[2]=pos_y[2];
				s1_angle.z[0]=pos_z;s1_angle.z[1]=pos_z;s1_angle.z[2]=pos_z;
				circle_logic(0,s1_angle);
				vTaskDelay(60);
				circle_logic(1,s1_angle);
			}
			
			else if(rx_oder.target_oder2[0]=='1' && rx_oder.target_oder2[1]=='3' && rx_oder.target_oder2[2]=='2')		//�죬������
			{
				s1_angle.circle_pos[0]= POS_GM[1]; s1_angle.circle_pos[1]=POS_GM[2]; s1_angle.circle_pos[2]=POS_GM[0];
				s1_angle.y[0]=pos_y[1];s1_angle.y[1]=pos_y[2];s1_angle.y[2]=pos_y[0];
				s1_angle.z[0]=pos_z;s1_angle.z[1]=pos_z;s1_angle.z[2]=pos_z;
				circle_logic(0,s1_angle);
				vTaskDelay(60);
				circle_logic(1,s1_angle);
			}
			else if(rx_oder.target_oder2[0]=='2' && rx_oder.target_oder2[1]=='1' && rx_oder.target_oder2[2]=='3')		//�̣��죬��
			{
				s1_angle.circle_pos[0]= POS_GM[0]; s1_angle.circle_pos[1]=POS_GM[1]; s1_angle.circle_pos[2]=POS_GM[2];
				s1_angle.y[0]=pos_y[0];s1_angle.y[1]=pos_y[1];s1_angle.y[2]=pos_y[2];
				s1_angle.z[0]=pos_z;s1_angle.z[1]=pos_z;s1_angle.z[2]=pos_z;
				circle_logic(0,s1_angle);
				vTaskDelay(60);
				circle_logic(1,s1_angle);
			}
			else if(rx_oder.target_oder2[0]=='2' && rx_oder.target_oder2[1]=='3' && rx_oder.target_oder2[2]=='1')		//�̣�������
			{
				s1_angle.circle_pos[0]= POS_GM[0]; s1_angle.circle_pos[1]=POS_GM[2]; s1_angle.circle_pos[2]=POS_GM[1];
				s1_angle.y[0]=pos_y[0];s1_angle.y[1]=pos_y[2];s1_angle.y[2]=pos_y[1];
				s1_angle.z[0]=pos_z;s1_angle.z[1]=pos_z;s1_angle.z[2]=pos_z;
				circle_logic(0,s1_angle);
				vTaskDelay(60);
				circle_logic(1,s1_angle);
			}
			else if(rx_oder.target_oder2[0]=='3' && rx_oder.target_oder2[1]=='2' && rx_oder.target_oder2[2]=='1')		//�����̣���
			{
				s1_angle.circle_pos[0]= POS_GM[2]; s1_angle.circle_pos[1]=POS_GM[0]; s1_angle.circle_pos[2]=POS_GM[1];
				s1_angle.y[0]=pos_y[2];s1_angle.y[1]=pos_y[0];s1_angle.y[2]=pos_y[1];
				s1_angle.z[0]=pos_z;s1_angle.z[1]=pos_z;s1_angle.z[2]=pos_z;
				circle_logic(0,s1_angle);
				vTaskDelay(60);
				circle_logic(1,s1_angle);
			}
			else if(rx_oder.target_oder2[0]=='3' && rx_oder.target_oder2[1]=='1' && rx_oder.target_oder2[2]=='2')		//�����죬��
			{
				s1_angle.circle_pos[0]= POS_GM[2]; s1_angle.circle_pos[1]=POS_GM[1]; s1_angle.circle_pos[2]=POS_GM[0];
				s1_angle.y[0]=pos_y[2];s1_angle.y[1]=pos_y[1];s1_angle.y[2]=pos_y[0];
				s1_angle.z[0]=pos_z;s1_angle.z[1]=pos_z;s1_angle.z[2]=pos_z;
				circle_logic(0,s1_angle);
				vTaskDelay(60);
				circle_logic(1,s1_angle);
			}
		}	
		vTaskDelay(100);
}
void Action_WORK2(int mode)			//
{
//-------------try code-------------//
	
//		rx_oder.target_oder1[0]='1';
//		rx_oder.target_oder1[1]='2';
//		rx_oder.target_oder1[2]='3';
//		rx_oder.target_oder2[0]='1';
//		rx_oder.target_oder2[1]='2';
//		rx_oder.target_oder2[2]='3';
	
//-------------try code-------------//
	

		Mearm_Move(scan_circle2_0);
		GM_detect();
		vTaskDelay(600);
		line_correct(0);
		if(mode==1)
		{
			Mearm_Move(scan_circle2);
			vTaskDelay(460);
			round_correct2(1);
		}
		else 
		{
			Mearm_Move(scan_circle2_2);
			vTaskDelay(460);
			round_correct2(2);
		}
		vTaskDelay(300);
		Mearm_Move(scan_circle2_0);
		vTaskDelay(360);
		
		s1_angle.obj_pos[0] = 0;
		s1_angle.obj_pos[1] = 180;
		s1_angle.obj_pos[2] = -90;

		if(mode==1)
		{
			if(rx_oder.target_oder1[0]=='1' && rx_oder.target_oder1[1]=='2' && rx_oder.target_oder1[2]=='3')		//�죬�̣���
			{			
				s1_angle.circle_pos[0]= POS_GM_S[1]; s1_angle.circle_pos[1]=POS_GM_S[0]; s1_angle.circle_pos[2]=POS_GM_S[2];
				s1_angle.y[0]=pos_y[1];s1_angle.y[1]=pos_y[0];s1_angle.y[2]=pos_y[2];
				s1_angle.z[0]=pos_z;s1_angle.z[1]=pos_z;s1_angle.z[2]=pos_z;
				circle_logic_2(s1_angle);
			}
			else if(rx_oder.target_oder1[0]=='1' && rx_oder.target_oder1[1]=='3' && rx_oder.target_oder1[2]=='2')		//�죬������
			{
				s1_angle.circle_pos[0]= POS_GM_S[1]; s1_angle.circle_pos[1]=POS_GM_S[2]; s1_angle.circle_pos[2]=POS_GM_S[0];
				s1_angle.y[0]=pos_y[1];s1_angle.y[1]=pos_y[2];s1_angle.y[2]=pos_y[0];
				s1_angle.z[0]=pos_z;s1_angle.z[1]=pos_z;s1_angle.z[2]=pos_z;
				circle_logic_2(s1_angle);
			}
			else if(rx_oder.target_oder1[0]=='2' && rx_oder.target_oder1[1]=='1' && rx_oder.target_oder1[2]=='3')		//�̣��죬��
			{
				s1_angle.circle_pos[0]= POS_GM_S[0]; s1_angle.circle_pos[1]=POS_GM_S[1]; s1_angle.circle_pos[2]=POS_GM_S[2];
				s1_angle.y[0]=pos_y[0];s1_angle.y[1]=pos_y[1];s1_angle.y[2]=pos_y[2];
				s1_angle.z[0]=pos_z;s1_angle.z[1]=pos_z;s1_angle.z[2]=pos_z;
				circle_logic_2(s1_angle);
			}
			else if(rx_oder.target_oder1[0]=='2' && rx_oder.target_oder1[1]=='3' && rx_oder.target_oder1[2]=='1')		//�̣�������
			{
				s1_angle.circle_pos[0]= POS_GM_S[0]; s1_angle.circle_pos[1]=POS_GM_S[2]; s1_angle.circle_pos[2]=POS_GM_S[1];
				s1_angle.y[0]=pos_y[0];s1_angle.y[1]=pos_y[2];s1_angle.y[2]=pos_y[1];
				s1_angle.z[0]=pos_z;s1_angle.z[1]=pos_z;s1_angle.z[2]=pos_z;
				circle_logic_2(s1_angle);
			}			
			else if(rx_oder.target_oder1[0]=='3' && rx_oder.target_oder1[1]=='2' && rx_oder.target_oder1[2]=='1')		//�����̣���
			{
				s1_angle.circle_pos[0]= POS_GM_S[2]; s1_angle.circle_pos[1]=POS_GM_S[0]; s1_angle.circle_pos[2]=POS_GM_S[1];
				s1_angle.y[0]=pos_y[2];s1_angle.y[1]=pos_y[0];s1_angle.y[2]=pos_y[1];
				s1_angle.z[0]=pos_z;s1_angle.z[1]=pos_z;s1_angle.z[2]=pos_z;
				circle_logic_2(s1_angle);
			}			
			else if(rx_oder.target_oder1[0]=='3' && rx_oder.target_oder1[1]=='1' && rx_oder.target_oder1[2]=='2')		//�����죬��
			{
				s1_angle.circle_pos[0]= POS_GM_S[2]; s1_angle.circle_pos[1]=POS_GM_S[1]; s1_angle.circle_pos[2]=POS_GM_S[0];
				s1_angle.y[0]=pos_y[2];s1_angle.y[1]=pos_y[1];s1_angle.y[2]=pos_y[0];
				s1_angle.z[0]=pos_z;s1_angle.z[1]=pos_z;s1_angle.z[2]=pos_z;
				circle_logic_2(s1_angle);
			}
		}
		
		else
		{
			if(rx_oder.target_oder2[0]=='1' && rx_oder.target_oder2[1]=='2' && rx_oder.target_oder2[2]=='3')		//�죬�̣���
			{			
				s1_angle.circle_pos[0]= POS_GM_S[1]; s1_angle.circle_pos[1]=POS_GM_S[0]; s1_angle.circle_pos[2]=POS_GM_S[2];
				s1_angle.y[0]=pos_y[1];s1_angle.y[1]=pos_y[0];s1_angle.y[2]=pos_y[2];
				s1_angle.z[0]=pos_z2;s1_angle.z[1]=pos_z2;s1_angle.z[2]=pos_z2;
				circle_logic_2(s1_angle);
			}
			else if(rx_oder.target_oder2[0]=='1' && rx_oder.target_oder2[1]=='3' && rx_oder.target_oder2[2]=='2')		//�죬������
			{
				s1_angle.circle_pos[0]= POS_GM_S[1]; s1_angle.circle_pos[1]=POS_GM_S[2]; s1_angle.circle_pos[2]=POS_GM_S[0];
				s1_angle.y[0]=pos_y[1];s1_angle.y[1]=pos_y[2];s1_angle.y[2]=pos_y[0];
				s1_angle.z[0]=pos_z2;s1_angle.z[1]=pos_z2;s1_angle.z[2]=pos_z2;
				circle_logic_2(s1_angle);
			}
			else if(rx_oder.target_oder2[0]=='2' && rx_oder.target_oder2[1]=='1' && rx_oder.target_oder2[2]=='3')		//�̣��죬��
			{
				s1_angle.circle_pos[0]= POS_GM_S[0]; s1_angle.circle_pos[1]=POS_GM_S[1]; s1_angle.circle_pos[2]=POS_GM_S[2];
				s1_angle.y[0]=pos_y[0];s1_angle.y[1]=pos_y[1];s1_angle.y[2]=pos_y[2];
				s1_angle.z[0]=pos_z2;s1_angle.z[1]=pos_z2;s1_angle.z[2]=pos_z2;
				circle_logic_2(s1_angle);
			}
			else if(rx_oder.target_oder2[0]=='2' && rx_oder.target_oder2[1]=='3' && rx_oder.target_oder2[2]=='1')		//�̣�������
			{
				s1_angle.circle_pos[0]= POS_GM_S[0]; s1_angle.circle_pos[1]=POS_GM_S[2]; s1_angle.circle_pos[2]=POS_GM_S[1];
				s1_angle.y[0]=pos_y[0];s1_angle.y[1]=pos_y[2];s1_angle.y[2]=pos_y[1];
				s1_angle.z[0]=pos_z2;s1_angle.z[1]=pos_z2;s1_angle.z[2]=pos_z2;
				circle_logic_2(s1_angle);
			}			
			else if(rx_oder.target_oder2[0]=='3' && rx_oder.target_oder2[1]=='2' && rx_oder.target_oder2[2]=='1')		//�����̣���
			{
				s1_angle.circle_pos[0]= POS_GM_S[2]; s1_angle.circle_pos[1]=POS_GM_S[0]; s1_angle.circle_pos[2]=POS_GM_S[1];
				s1_angle.y[0]=pos_y[2];s1_angle.y[1]=pos_y[0];s1_angle.y[2]=pos_y[1];
				s1_angle.z[0]=pos_z2;s1_angle.z[1]=pos_z2;s1_angle.z[2]=pos_z2;
				circle_logic_2(s1_angle);
			}			
			else if(rx_oder.target_oder2[0]=='3' && rx_oder.target_oder2[1]=='1' && rx_oder.target_oder2[2]=='2')		//�����죬��
			{
				s1_angle.circle_pos[0]= POS_GM_S[2]; s1_angle.circle_pos[1]=POS_GM_S[1]; s1_angle.circle_pos[2]=POS_GM_S[0];
				s1_angle.y[0]=pos_y[2];s1_angle.y[1]=pos_y[1];s1_angle.y[2]=pos_y[0];
				s1_angle.z[0]=pos_z2;s1_angle.z[1]=pos_z2;s1_angle.z[2]=pos_z2;
				circle_logic_2(s1_angle);
			}
		}
		shou(0);
		GM_detect();
		vTaskDelay(300);	
}

void Action_Back(void)	//�ص�������
{
	move_to(0, 820, 0);
	Waitfinishmoving();
	line_correct(270);
	move_to(1570, 0, 0);
	Waitfinishmoving();
	line_correct(270);
	move_to(0, -370, 0);
	Waitfinishmoving();
	Mearm_Move(scan_cor);			
	vTaskDelay(2000);
	position_correct();
	vTaskDelay(1000);
	Mearm_Move(scan_cor_0);	
}

void Put_ON_circle(int mode,int put_angle,int put_pos,float y,float z) //�ӳ��Ϸŵ�����
{
	move_grap(put_pos);		//��

	move_get_fang(put_angle,y,z);	//��
}

void Grab_up(int mode,int put_angle,int put_pos,float y,float z)		//ץ������
{
	back_grab(put_angle,y,z);
	
	move_get_zhua(put_angle,y,z);		//��ǰץ

	up_grab(put_angle,y);			//����

	move_put(put_pos);					//����
}

void Grab_up_2(int mode,int put_angle,int put_pos,float y,float z)		//ץ������
{

	back_grab_2(put_angle,y,z);
	
	move_get_zhua2(put_angle,y,z);		//ץ
	
	up_grab(put_angle,y);			//����

	move_put(put_pos);					//����
}

//Բ�������߼�
void circle_logic(uint8_t mode,const GM_PUTANGLE T)
{
			if(mode ==0)			//����鵽Բ����
			{	
			Put_ON_circle(2,T.circle_pos[0],T.obj_pos[0],T.y[0],T.z[0]);					//����1 Բ���ĽǶȣ�����2 �۵ĽǶ�	
			Put_ON_circle(2,T.circle_pos[1],T.obj_pos[1],T.y[1],T.z[1]);
			Put_ON_circle(2,T.circle_pos[2],T.obj_pos[2],T.y[2],T.z[2]);
			shou(270);
			GM_detect();
			vTaskDelay(600);
			}
			else if(mode ==1)			//ץ���س���
			{
			Grab_up_2(0,T.circle_pos[0],T.obj_pos[2],T.y[0],T.z[0]);	
			Grab_up_2(0,T.circle_pos[1],T.obj_pos[1],T.y[1],T.z[1]);
			Grab_up_2(0,T.circle_pos[2],T.obj_pos[0],T.y[2],T.z[2]);
			}		
}
//���ӹ�Բ�������߼�
void circle_logic_2(GM_PUTANGLE T)
{
			Put_ON_circle(3,T.circle_pos[0],T.obj_pos[0],T.y[0],T.z[0]);					//����1 Բ���ĽǶȣ�����2 �۵ĽǶ�	
			Put_ON_circle(3,T.circle_pos[1],T.obj_pos[1],T.y[1],T.z[1]);
			Put_ON_circle(3,T.circle_pos[2],T.obj_pos[2],T.y[2],T.z[2]);
}
