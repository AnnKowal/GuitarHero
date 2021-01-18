#include "frdm_bsp.h"
#include "song.h"
#define CLK_DIS 					0x00
#define MCGFLLCLK 				0x01
#define OSCERCLK					0x02
#define MCGIRCLK					0x03
static unsigned char temp=0;
static unsigned char temp2=0;
static unsigned char temp3=0;
static unsigned char temp4=0;
uint8_t  piosenka_FULL = 1;
static uint32_t dlugosc = 1200000;

static uint8_t znak=5;
void UART0_read2(void);
void UART0_Init(void);
uint8_t UART0_read(void);
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

	while(!(UART0->S1 & UART0_S1_RDRF_MASK)){}
		temp=UART0->D;	
		if(!piosenka_FULL)
		{
			piosenka_FULL=1;
		}

	return temp;
}

void UART0_read2(){
	
	while(!(UART0->S1 & UART0_S1_TDRE_MASK));
	UART0->D = znak;
	for (uint16_t k=0; k<dlugosc; k++){	
			temp2=UART0_read();
			
		if (k%4==3)
		{
			if (temp2=='a' || temp2=='b' || temp2=='c' || temp2=='d' || temp2 == 'e' || temp2=='f')
			{temp4=temp4*16+(temp2-87);}
			else{temp4=temp4*16+(temp2-0x30);
			
			}
				TPM0_Play6(temp4);	
				while(!(UART0->S1 & UART0_S1_TDRE_MASK));			UART0->D = temp4;
			//	piosenka3[temp3]=temp4;
			//temp3++;	
			//TPM0->CONTROLS[2].CnV = temp4; 

			}
		else if(k%4==2)
		{
			if (temp2=='a' || temp2=='b' || temp2=='c' || temp2=='d' || temp2 == 'e' || temp2=='f')
			{temp4=temp4+(temp2-87);}
			else
			{temp4=temp4+(temp2-0x30);}
		}
		else
		{
			temp4=0;
		}
			piosenka_FULL=0;
	}
}
