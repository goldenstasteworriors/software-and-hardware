#include "myqueue.h"


QueueHandle_t speedLFQueueHandle, speedLBQueueHandle, speedRFQueueHandle, speedRBQueueHandle, yawQueueHandle;	//控制电机速度	
QueueHandle_t bottom_moveHandle;
QueueHandle_t xposPIRQueueHandle, yposPIRQueueHandle, yawPIRQueueHandle;			//由红外传感器获得的坐标
QueueHandle_t xposIMUQueueHandle, yposIMUQueueHandle, yawIMUQueueHandle;			//由陀螺仪获得的坐标
QueueHandle_t xposRefQueueHandle, yposRefQueueHandle, yawRefQueueHandle;			//修正后的坐标

QueueHandle_t G6020AngleQueueHandle;			//云台角度
QueueHandle_t G6020AnleRefQueueHandle;		//云台修正角度
QueueHandle_t ArmAttitudeQueueHandle;		//机械臂角度控制
QueueHandle_t ArmhandstateQueueHandle;		//机械臂状态
QueueHandle_t RasperryDataQueueHandle, RasperryitemQueueHandle, RasperrycircleQueueHandle, RasperryQRQueueHandle;	//树莓派物料，圆圈，横线数据
QueueHandle_t RasperryfianlQueueHandle,WORK1QueueHandle,WORK2QueueHandle;
QueueHandle_t stratQueueHandle;
void queue_init()
{
	
  speedLFQueueHandle = xQueueCreate(1, sizeof(float));
	speedLBQueueHandle = xQueueCreate(1, sizeof(float));
	speedRFQueueHandle = xQueueCreate(1, sizeof(float));
	speedRBQueueHandle = xQueueCreate(1, sizeof(float));
	yawQueueHandle = xQueueCreate(1, sizeof(float));	//控制电机速度	

	bottom_moveHandle = xQueueCreate(1, sizeof(POSITON));
	
  xposPIRQueueHandle = xQueueCreate(1, sizeof(float));
	yposPIRQueueHandle = xQueueCreate(1, sizeof(float));
	yawPIRQueueHandle = xQueueCreate(1, sizeof(float));			//由红外传感器获得的坐标
  xposIMUQueueHandle = xQueueCreate(1, sizeof(float));
	yposIMUQueueHandle = xQueueCreate(1, sizeof(float)); 
	yawIMUQueueHandle = xQueueCreate(1, sizeof(float));			//由陀螺仪获得的坐标
  xposRefQueueHandle = xQueueCreate(1, sizeof(float));
	yposRefQueueHandle = xQueueCreate(1, sizeof(float)); 
	yawRefQueueHandle = xQueueCreate(1, sizeof(float));			//修正后的坐标

  G6020AngleQueueHandle = xQueueCreate(10, sizeof(float));			//云台角度
  G6020AnleRefQueueHandle = xQueueCreate(10, sizeof(float));		//云台修正角度
  ArmAttitudeQueueHandle = xQueueCreate(1, sizeof(MecArmAttiSturcture));		//机械臂角度控制
  ArmhandstateQueueHandle = xQueueCreate(1, sizeof(float));		//机械臂状态
  
	RasperryDataQueueHandle = xQueueCreate(1, sizeof(uint8_t));
	RasperryitemQueueHandle = xQueueCreate(1, sizeof(uint8_t));	//物料颜色数据
	RasperrycircleQueueHandle = xQueueCreate(10, sizeof(double));
	RasperryfianlQueueHandle = xQueueCreate(1, sizeof(uint8_t));
	RasperryQRQueueHandle = xQueueCreate(1, sizeof(uint8_t));	//二维码数据
	WORK1QueueHandle = xQueueCreate(1, sizeof(uint8_t));
	WORK2QueueHandle = xQueueCreate(1, sizeof(uint8_t));
	stratQueueHandle = xQueueCreate(1, sizeof(uint8_t));
}
