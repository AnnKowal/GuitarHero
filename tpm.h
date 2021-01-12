#ifndef TPM_H
#define TPM_H
#define CLK_DIS 					0x00
#define MCGFLLCLK 				0x01
#define OSCERCLK					0x02
#define MCGIRCLK					0x03

#include "frdm_bsp.h"

void UART0_read(void);
void UART0_Init(void);
void tpm1_init_pwm(void);

void TPM0_Init(void);
void TPM0_Play6(void);
void TPM0_Pause(void);

#endif 
