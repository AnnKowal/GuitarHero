#include "uart.h"

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
	
	//NVIC_SetPriority(TPM0_IRQn, 2);  //priorytet przerwania
	
	//NVIC_EnableIRQ(UART0_IRQn);
	//NVIC_ClearPendingIRQ(UART0_IRQn);
}
