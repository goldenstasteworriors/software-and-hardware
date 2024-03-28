#ifndef _TASKHMI_H
#define _TASKHMI_H
#include "stdint.h"
#include "main.h"

void HMISends(uint8_t *buf1);
void HMISendb(uint8_t k);
void HMISendstart(void);
void textHMI(char *buf, float var);
void numHMI(char *buf, uint8_t var);
void lineHMI(char *buf, uint8_t ExchangeSpeed1);
void floatHMI(char *buf, uint8_t num, uint8_t vvs);


#endif
