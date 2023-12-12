#ifndef __PWM_H
#define	__PWM_H

#include "stm32f10x.h"

void PWM_Int(u16 arr,u16 psc);
void Set_PWMA(int PWM);
void Set_PWMB(int PWM);

#endif

