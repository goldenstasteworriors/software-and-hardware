#include "myqueue.h"


QueueHandle_t speedLFQueueHandle, speedLBQueueHandle, speedRFQueueHandle, speedRBQueueHandle, yawQueueHandle;	//���Ƶ���ٶ�	
QueueHandle_t bottom_moveHandle;
QueueHandle_t xposPIRQueueHandle, yposPIRQueueHandle, yawPIRQueueHandle;			//�ɺ��⴫������õ�����
QueueHandle_t xposIMUQueueHandle, yposIMUQueueHandle, yawIMUQueueHandle;			//�������ǻ�õ�����
QueueHandle_t xposRefQueueHandle, yposRefQueueHandle, yawRefQueueHandle;			//�����������

QueueHandle_t G6020AngleQueueHandle;			//��̨�Ƕ�
QueueHandle_t G6020AnleRefQueueHandle;		//��̨�����Ƕ�
QueueHandle_t ArmAttitudeQueueHandle;		//��е�۽Ƕȿ���
QueueHandle_t ArmhandstateQueueHandle;		//��е��״̬
QueueHandle_t RasperryDataQueueHandle, RasperryitemQueueHandle, RasperrycircleQueueHandle, RasperryQRQueueHandle;	//��ݮ�����ϣ�ԲȦ����������
QueueHandle_t RasperryfianlQueueHandle,WORK1QueueHandle,WORK2QueueHandle;
QueueHandle_t stratQueueHandle;
void queue_init()
{
	
  speedLFQueueHandle = xQueueCreate(1, sizeof(float));
	speedLBQueueHandle = xQueueCreate(1, sizeof(float));
	speedRFQueueHandle = xQueueCreate(1, sizeof(float));
	speedRBQueueHandle = xQueueCreate(1, sizeof(float));
	yawQueueHandle = xQueueCreate(1, sizeof(float));	//���Ƶ���ٶ�	

	bottom_moveHandle = xQueueCreate(1, sizeof(POSITON));
	
  xposPIRQueueHandle = xQueueCreate(1, sizeof(float));
	yposPIRQueueHandle = xQueueCreate(1, sizeof(float));
	yawPIRQueueHandle = xQueueCreate(1, sizeof(float));			//�ɺ��⴫������õ�����
  xposIMUQueueHandle = xQueueCreate(1, sizeof(float));
	yposIMUQueueHandle = xQueueCreate(1, sizeof(float)); 
	yawIMUQueueHandle = xQueueCreate(1, sizeof(float));			//�������ǻ�õ�����
  xposRefQueueHandle = xQueueCreate(1, sizeof(float));
	yposRefQueueHandle = xQueueCreate(1, sizeof(float)); 
	yawRefQueueHandle = xQueueCreate(1, sizeof(float));			//�����������

  G6020AngleQueueHandle = xQueueCreate(10, sizeof(float));			//��̨�Ƕ�
  G6020AnleRefQueueHandle = xQueueCreate(10, sizeof(float));		//��̨�����Ƕ�
  ArmAttitudeQueueHandle = xQueueCreate(1, sizeof(MecArmAttiSturcture));		//��е�۽Ƕȿ���
  ArmhandstateQueueHandle = xQueueCreate(1, sizeof(float));		//��е��״̬
  
	RasperryDataQueueHandle = xQueueCreate(1, sizeof(uint8_t));
	RasperryitemQueueHandle = xQueueCreate(1, sizeof(uint8_t));	//������ɫ����
	RasperrycircleQueueHandle = xQueueCreate(10, sizeof(double));
	RasperryfianlQueueHandle = xQueueCreate(1, sizeof(uint8_t));
	RasperryQRQueueHandle = xQueueCreate(1, sizeof(uint8_t));	//��ά������
	WORK1QueueHandle = xQueueCreate(1, sizeof(uint8_t));
	WORK2QueueHandle = xQueueCreate(1, sizeof(uint8_t));
	stratQueueHandle = xQueueCreate(1, sizeof(uint8_t));
}
