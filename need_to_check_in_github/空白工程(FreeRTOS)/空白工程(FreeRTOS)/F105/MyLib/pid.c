#include "main.h"
#include "pid.h"

/**
  * @brief  PID�����㷨
  * @param  PID_Struct *P  PID�����ṹ��
  *         ActualValue    PID���㷴��������ǰ��ʵ���ֵ��
  * @retval PID�����������ֵ
  */
float PID_Calc(pid_Typedef *P, float ActualValue)
{
    P->PreError = P->SetPoint - ActualValue;
    P->dError = P->PreError - P->LastError;

    P->SumError += P->PreError;
    P->LastError = P->PreError;

    if(P->SumError >= P->IMax)
        P->SumError = P->IMax;
    else if(P->SumError <= -P->IMax)
        P->SumError = -P->IMax;

    P->POut = P->P * P->PreError;
    P->IOut = P->I * P->SumError;
    P->DOut = P->D * P->dError;

    return P->POut + P->IOut + P->DOut;
}
void PID_Par_Reset(pid_Typedef *P)
{
	P->P = 0;
	P->I = 0;
	P->D = 0;
	P->IMax = 0;
	P->SetPoint = 0;
	P->LastError = 0;
	P->PreError = 0;
	P->SumError = 0;
	P->dError = 0;
	P->POut = 0;
	P->DOut = 0;
	P->IOut = 0;
}

