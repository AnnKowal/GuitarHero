#include "tpm.h"
//#include "uart.h"
void TPM0_IRQHandler(void);
static uint8_t enable = 0;
static uint32_t upSampleCNT = 0;
static uint32_t probka = 0;
static uint32_t dlugosc = 3000;
static uint32_t probka_do_odt = 0;
static uint32_t upsampling = 10;
static uint8_t  play = 1;
static uint8_t  pause = 0;
static uint8_t  liczba= 0;
static uint8_t  empty=1;
uint8_t  piosenka_FULL = 0;
unsigned char temp=0;
unsigned char temp2=0;
static unsigned char piosenka2[];
static unsigned char piosenka3[3000];

static uint8_t znak=5;
static uint8_t znak1=2;
static uint8_t znak2=3;


void tpm1_init_pwm(void)
{
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	PORTA->PCR[12] = PORT_PCR_MUX(2);
	TPM1->SC |= TPM_SC_PS(7);
	TPM1->SC |= TPM_SC_CMOD(1);
	TPM1->MOD = 100;
	TPM1->SC &= ~TPM_SC_CPWMS_MASK; 
	TPM1->CONTROLS[0].CnSC |= (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK);
	TPM1->CONTROLS[0].CnV = 10;

}


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




void UART0_Init(void)
{
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;							
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;							
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(MCGFLLCLK);		
	PORTB->PCR[1] = PORT_PCR_MUX(2);								
	PORTB->PCR[2] = PORT_PCR_MUX(2);								
	
	UART0->C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK );		
	UART0->BDH = 0;
	UART0->BDL =91;		
	UART0->C4 &= ~UART0_C4_OSR_MASK;
	UART0->C4 |= UART0_C4_OSR(15);	
	UART0->C5 |= UART0_C5_BOTHEDGE_MASK;	
	UART0->C2 |= UART0_C2_RIE_MASK;		
	UART0->C2 |= (UART0_C2_TE_MASK | UART0_C2_RE_MASK);		
}

uint8_t UART0_read(){
	while(!(UART0->S1 & UART0_S1_RDRF_MASK))
	{}
		temp=UART0->D;	
		if(!piosenka_FULL)
		{
			piosenka2[0] = temp;	
			piosenka_FULL=1;
		}
	

	return temp;
}

void UART0_read2(){
	while(!(UART0->S1 & UART0_S1_TDRE_MASK));
	UART0->D = znak;
	for (uint16_t k=0; k<dlugosc; k++){
			temp2=UART0_read();
			//while(!(UART0->S1 & UART0_S1_TDRE_MASK));
			//UART0->D = temp2;
			piosenka3[k]=temp2;
			piosenka_FULL=0;
	}
//	empty=0;
	
}

void UART0_read3(){
	while(!(UART0->S1 & UART0_S1_TDRE_MASK));
	UART0->D = znak1;
	for (uint16_t k=0; k<dlugosc; k++){
			temp2=UART0_read();
			piosenka3[k]=temp2;
			piosenka_FULL=0;
	}
	
}

void TPM0_Play6(void) {   

	play=1;
	probka=0;
	pause=0;
}


void TPM0_Play0(void) {   
	//UART0_read2();
	play=1;
	probka=0;
	pause=0;
	//liczba=2;
}

void TPM0_Play1(void) {   
	//UART0_read3();
	play=1;
	probka=0;
	pause=0;

}

void TPM0_Pause(void){
	play=0;
	pause=1;
	
}
void TPM0_IRQHandler(void) {
						if (play==1) {
						//while(!(UART0->S1 & UART0_S1_TDRE_MASK));
						//UART0->D = znak2;
						if (upSampleCNT == 0){
							probka_do_odt=probka++;
					
							TPM0->CONTROLS[2].CnV = piosenka3[probka_do_odt]; 
					
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
			

						
						
				TPM0->CONTROLS[0].CnSC |= TPM_CnSC_CHF_MASK; 
}


	