
#include "spi.h"



void delayMs(int n)
{
    volatile int i, j;
    for(i = 0 ; i < n; i++)
        for(j = 0; j < 3500; j++)
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
	SPI0->BR = 0x70; // baud rate = 1,3 MHz
 	 SPI0->C1 |= SPI_C1_SPE_MASK; // spi system enabled
	SPI0->C1 &= ~(SPI_C1_CPOL_MASK // active high spi clock
								|SPI_C1_SPIE_MASK // inhibited interrupts from SPRF and MODF 
								|SPI_C1_CPHA_MASK); // first edge on SPSCK occured at the middle of the first cycle of data transfer
	PORTB->PCR[SCE] = PORT_PCR_MUX(1);//SCE
	PORTB->PCR[RST] = PORT_PCR_MUX(1);//RST
	PORTB->PCR[D_C] = PORT_PCR_MUX(1);// D/C
	PTB->PDDR |= (1<<SCE) | (1<<RST) | (1<<D_C); // set SCE, RST and D/C as outputs
	PTB->PSOR = (1<<SCE) | (1<<RST) | (1<<D_C); // RST, SCE: set high, active as low; D/C: select data mode


	PTB->PCOR |= (1<<RST); // turn on RST 
	delayMs(100);///more if not enough
	PTB->PSOR |= (1<<RST) ; // turn off RST
	delayMs(100);
	PTB->PCOR |= (1<<D_C); // set command mode
	spi_write(0x21);//select extended instruction set
	spi_write(0xC7); //contrast
	spi_write(0x04);//temperature coefficient
	spi_write(0x20);//normal instruction set
	spi_write(0x0D); // inverse mode
	spi_write(0x0C);//display control - set normal mode
	
}

void spi_write_data(const unsigned char bitmap[])
{
	PTB->PCOR |= (1<<D_C);
	spi_write(0x40);
	spi_write(0x80);
	PTB->PSOR |= (1<<D_C); // select data mode
	
		for (unsigned int i = 0; i< 505; i++)//((sizeof bitmap) / (sizeof bitmap[0])); i++)
		{spi_write(bitmap[i]);	
			
		}

}
 void spi_write(uint8_t address)
 {
	 volatile char dummy;
	 PTB->PCOR |= (1<<SCE);	//enable Chip Select	
		while(!(SPI0->S & 0x20)){} //wait until buffer not empty
		SPI0->D = address; // send address
	while(!(SPI0->S & 0x80)){} // wait for the end of the data
		dummy = SPI0->D;
		PTB->PSOR |= (1<<SCE);	 // disable Chip Select
 }
 
