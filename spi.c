#include "MKL05Z4.h"
#include "tpm.c"
void delayMs (int n);
void spi_init(void);
void spi_write(const unsigned char bitmap[]);

void delayMs(int n)
{
    int i, j;
    for(i = 0 ; i < n; i++)
        for(j = 0; j < 1000; j++)
            {}  
}
void spi_init(void)
{
	SIM->SCGC4 |= SIM_SCGC4_SPI0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	
	PORTB->PCR[0] = PORT_PCR_MUX(3); ///SCK
	PORTA->PCR[7] = PORT_PCR_MUX(3); ///MOSI
	SPI0->C1 = SPI_C1_MSTR_MASK;//set as master
	SPI0->BR = 0x60; // baud rate = 1,3 MHz
  SPI0->C1 |= SPI_C1_SPE_MASK; // spi system enabled
	
	PORTB->PCR[11] = PORT_PCR_MUX(1);//SCE
	PORTB->PCR[10] = PORT_PCR_MUX(1);//RST
	PORTB->PCR[7] = PORT_PCR_MUX(1);// D/C
	PTB->PDDR |= (1<<11) | (1<<10) | (1<<7); // set SCE, RST and D/C as outputs
	PTB->PSOR = (1<<10) | (1<<7) | (1<<11); // RST, SCE: set high, active as low; D/C: select data mode


	PTB->PCOR |= (1<<10); // turn on RST 
	delayMs(1);///more if not enough
	PTB->PSOR |= (1<<10) ; // turn off RST
	PTB->PCOR |= (1<<7); // set command mode
	PTB->PCOR |= (1<<11); // enable Chip Select
	
	while(!(SPI0->S & 0x20)){} //wait until buffer not empty
		SPI0->D = 0x21;
	while(!(SPI0->S & 0x80)){}
		PTB->PSOR |= (1<<11);
PTB->PCOR |= (1<<11);		
		while(!(SPI0->S & 0x20)){} //wait until buffer not empty
		SPI0->D = 0x90;//////////////////////
	while(!(SPI0->S & 0x80)){}
		PTB->PSOR |= (1<<11);	
		PTB->PCOR |= (1<<11);
		while(!(SPI0->S & 0x20)){} //wait until buffer not empty
		SPI0->D = 0x20;
	while(!(SPI0->S & 0x80)){}
		PTB->PSOR |= (1<<11);


PTB->PCOR |= (1<<11);		
		while(!(SPI0->S & 0x20)){} //wait until buffer not empty
		SPI0->D = 0x0C;
	while(!(SPI0->S & 0x80)){}
		PTB->PSOR |= (1<<11);	
		PTB->PCOR |= (1<<11);		
		while(!(SPI0->S & 0x20)){} //wait until buffer not empty
		SPI0->D = 0x0D;
	while(!(SPI0->S & 0x80)){}
		PTB->PSOR |= (1<<11);	
}

void spi_write(const unsigned char bitmap[])
{
	PTB->PSOR |= (1<<7); // select data mode

	PTB->PCOR |= (1<<11); // enable Chip Select
	
		
	while(!(SPI0->S & 0x20)){} //wait until buffer not empty
		for (unsigned int i = 0; (sizeof bitmap) / (sizeof bitmap[0]); i++)
		{SPI0->D = bitmap[i];		}
	while(!(SPI0->S & 0x80)){}
	PTB->PSOR |= (1<<11);	
}
