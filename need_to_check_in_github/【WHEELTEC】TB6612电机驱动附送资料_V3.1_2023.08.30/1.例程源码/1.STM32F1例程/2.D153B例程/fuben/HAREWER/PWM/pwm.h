#ifndef __PWM_H
#define	__PWM_H

#include "stm32f10x.h"

void PWM1_Int(u16 arr,u16 psc);
void PWM2_Int(u16 arr,u16 psc);
void Set_PWMA(int PWM);
void Set_PWMB(int PWM);
void Set_PWMC(int PWM);
void Set_PWMD(int PWM);

#endif

