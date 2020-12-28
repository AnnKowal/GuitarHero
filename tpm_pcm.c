#include "tpm_pcm.h"
#include "piosenka.h"



void TPM0_IRQHandler(void);

static uint8_t enable = 0;
static uint32_t upSampleCNT = 0;
static uint32_t probka = 0;
static uint32_t probka_do_odt = 0;
static uint32_t upsampling = 10;
static uint8_t  play = 1;
static uint8_t  pause1 = 0;
static uint8_t  pause = 0;

void TPM0_Init(void) {
			
  SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;		//wlaczenie maski 
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);    //wybor zrodla zegara

	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; //podlaczenie zegara do portu B
	PORTB->PCR[7] = PORT_PCR_MUX(2);		//wybor multipleksera	
	
	TPM0->SC |= TPM_SC_PS(2);  	//ustawienie prescalera 				  
	TPM0->SC |= TPM_SC_CMOD(1);	//wybor zegara				  

	TPM0->MOD = 255; //wybor wartosci modulo										  
	

	TPM0->SC &= ~TPM_SC_CPWMS_MASK; //zliczanie w gore		
	TPM0->CONTROLS[2].CnSC |= (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK); 
	TPM0->CONTROLS[2].CnV = 0; 
	
	

	TPM0->SC &= ~TPM_SC_CPWMS_MASK;
	TPM0->CONTROLS[0].CnSC |= (TPM_CnSC_MSA_MASK | TPM_CnSC_ELSA_MASK);
	TPM0->CONTROLS[0].CnV = 0;
  
	TPM0->CONTROLS[0].CnSC |= TPM_CnSC_CHIE_MASK; //zezwolenie na przerwanie
	
	NVIC_SetPriority(TPM0_IRQn, 1);  //priorytet przerwania

	NVIC_ClearPendingIRQ(TPM0_IRQn); 
	NVIC_EnableIRQ(TPM0_IRQn);	//zezwolenie na przerwanie
	
	enable= 1; 
}

void TPM0_Play(void) {   
	play = 1;
	pause=0;
	
	if (pause1==1){
	probka=probka_do_odt;
	}
	else{
		probka=0;
	}
	pause1=0;
}

void TPM0_Pause(void){
	pause=1;
	play=0;
	pause1=1;
	
}

void TPM0_IRQHandler(void) {
	
	if (play==1 && pause==0) {
		if (upSampleCNT == 0){
			probka_do_odt=probka++;
			TPM0->CONTROLS[2].CnV = piosenka[probka_do_odt]; 
		}	
		if (probka > dlugosc ) {
			play = 0;         
			TPM0->CONTROLS[2].CnV = 0;
	
		}
	
		if (++upSampleCNT > (upsampling-1)) 
		{
			upSampleCNT = 0;
		}
	}
		if (pause==1 ) {         
			TPM0->CONTROLS[2].CnV = 0;
			pause=0;
		}
			
	TPM0->CONTROLS[0].CnSC |= TPM_CnSC_CHF_MASK; 
}
