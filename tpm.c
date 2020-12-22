#include "MKL05Z4.h"
void tpm0_init_pwm(void);
void tpm0_init_pwm(void)
{
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	PORTA->PCR[5] = PORT_PCR_MUX(2);
	TPM0->SC |= TPM_SC_PS(7);
	TPM0->SC |= TPM_SC_CMOD(1);
	TPM0->MOD = 100;
	TPM0->SC &= ~TPM_SC_CPWMS_MASK; 
	TPM0->CONTROLS[5].CnSC |= (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK);
	TPM0->CONTROLS[5].CnV = 10;

}
	
