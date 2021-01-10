  
#ifndef TPM_H
#define TPM_H

#include "frdm_bsp.h"

void tpm1_init_pwm(void);

void TPM0_Init(void);

void TPM0_Play(void);

void TPM0_Pause(void);

void TPM0_IRQHandler(void);


#endif 
