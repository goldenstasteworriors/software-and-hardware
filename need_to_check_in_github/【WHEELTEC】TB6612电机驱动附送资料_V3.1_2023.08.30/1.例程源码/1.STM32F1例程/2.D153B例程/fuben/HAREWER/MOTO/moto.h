#ifndef __MOTO_H
#define	__MOTO_H

#include "stm32f10x.h"

void moto1(int mode);
void moto2(int mode);
int Velocity_A(int TargetVelocity, int CurrentVelocity);
int Velocity_B(int TargetVelocity, int CurrentVelocity);
int Velocity_C(int TargetVelocity, int CurrentVelocity);
int Velocity_D(int TargetVelocity, int CurrentVelocity);
#endif
